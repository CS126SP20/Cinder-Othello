// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <sqlite_modern_cpp.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include "cinder/ip/Checkerboard.h"

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using std::string;

using cinder::app::KeyEvent;

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;
using namespace ci;
using namespace ci::app;

audio::VoiceRef music_voice;
audio::VoiceRef move_voice;
audio::VoiceRef game_over_voice;
const char kNormalFont[] = "Arial";

const char kDbPath[] = "scoreboard.db";

using cinder::app::KeyEvent;

MyApp::MyApp(): leaderboard_{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  SetGameBoard();

  valid_moves = GetValidMoves();

  UpdateScores();

  background_ = gl::Texture2d::create(loadImage
      (loadAsset("othello_board.png")));

  reset_ = gl::Texture2d::create(loadImage
      (loadAsset("reset_button.png")));

  PlaySound("background");
}

void MyApp::update() {
  if (!music_voice->isPlaying()) { // If the music ended, repeat the music
    music_voice->start();
  }
}

void MyApp::draw() {
  gl::clear();
  const Rectf board_bounds(0, 0, kBoardBounds, kBoardBounds);
  gl::draw(background_, board_bounds);// Draws the game board

  if (IsGameOver()) {
    const Rectf reset_bounds(800, 400, 900, 500);
    gl::draw(reset_, reset_bounds);// Draws the reset button
  }

  DrawBoard();
  DrawScoresAndText();

  gl::color(Color(1,1,1));
}

void MyApp::keyDown(KeyEvent event) { }

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 24))
      .size(size)
      .color(color)
      .backgroundColor(ColorA(0, 0, 0, 0))
      .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawBoard() {
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      int xPos = i * kTileLength + kTileCenter;
      int yPos = j * kTileLength + kTileCenter;
      if (game_board[i][j] == "white") {
        gl::color(Color(1,1,1));
        gl::drawSolidCircle( vec2(xPos, yPos), kCirclePieceRadius);
      } else if (game_board[i][j] == "black") {
        gl::color(Color(0,0,0));
        gl::drawSolidCircle( vec2(xPos, yPos), kCirclePieceRadius);
      }
    }
  }

  for (auto& valid_move : valid_moves) {
    int xPos = valid_move.first * kTileLength + kTileCenter;
    int yPos = valid_move.second * kTileLength + kTileCenter;
    if (is_white_turn_) {
      gl::color(Color(1,1,1));
    } else {
      gl::color(Color(0,0,0));
    }
    gl::drawStrokedCircle(vec2(xPos, yPos), kCirclePieceRadius);
  }

}

void MyApp::mouseDown(cinder::app::MouseEvent event) {

  if (IsGameOver() && event.getX() >= 800 && event.getX() <= 900
    && event.getY() >= 400 && event.getY() <= 500) {
    ResetGame();
  }

  int x_tile_coordinate_ = event.getX();
  int y_tile_coordinate_ = event.getY();

  // The two lines below divide the x and y coordinates on the board by
  // 90 (pixel length of each square) to get the corresponding x and y
  // coordinates on the board (0 to 7)
  x_tile_coordinate_ = x_tile_coordinate_ / kTileLength;
  y_tile_coordinate_ = y_tile_coordinate_ / kTileLength;

  if (IsMoveValid(x_tile_coordinate_, y_tile_coordinate_)) {
    PlaySound("click");
    valid_moves.clear();
    if (is_white_turn_) {
      game_board[x_tile_coordinate_][y_tile_coordinate_] = "white";
    } else {
      game_board[x_tile_coordinate_][y_tile_coordinate_] = "black";
    }
    FlipPieces(x_tile_coordinate_, y_tile_coordinate_);
  } else {
    is_white_turn_ = !is_white_turn_;
  }
  is_white_turn_ = !is_white_turn_;
  valid_moves = GetValidMoves();

  if (valid_moves.empty()) {
    is_white_turn_ = !is_white_turn_;
    valid_moves = GetValidMoves();
  }

  if (IsGameOver()) {
    PlaySound("game over");
  }
}

void MyApp::FlipPieces(int& x_tile_coordinate_, int& y_tile_coordinate_) {
  string last_turn_color = "black";
  if (is_white_turn_) {
    last_turn_color = "white";
  }

  vector<std::pair<int, int>> to_flip;

  for (size_t i = 0; i < x_change.size(); i++) {
    int x = x_tile_coordinate_;
    int y = y_tile_coordinate_;

    for (int j = 0; j < kBoardSize; j++) {
      x += x_change[i];
      y += y_change[i];

      if (!InBounds(x, y)) {
        break;
      }
      if (game_board[x][y].empty()) { // Checks for empty string
        break;
      } else if (game_board[x][y] != last_turn_color) {
        to_flip.emplace_back(x, y); // Adds the pair of coordinates to to_flip
      } else { // == lastTurnColor
        for (const auto& pair : to_flip) {
          game_board[pair.first][pair.second] = last_turn_color;
        }
        break;
      }
    }
    to_flip.clear();
  }

  UpdateScores();
}


bool MyApp::InBounds(int x, int y) {
  return (x >= 0) && (x < kBoardSize) && (y >= 0) && (y < kBoardSize);
}

void MyApp::UpdateScores() {
  white_score = 0;
  black_score = 0;
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      if (game_board[j][i] == "white") {
        white_score++;
      } else if (game_board[j][i] == "black") {
        black_score++;
      }
    }
  }
}

bool MyApp::IsMoveValid(int& x_tile_coordinate_, int& y_tile_coordinate_) {
  if (!InBounds(x_tile_coordinate_, y_tile_coordinate_)) {
    return false;
  }
  string last_turn_color = "black";
  if (is_white_turn_) {
    last_turn_color = "white";
  }

  // If there's already a piece at that spot on the board, it is not
  // possible for it to be a valid move.
  if (!game_board[x_tile_coordinate_][y_tile_coordinate_].empty()) {
    return false;
  }

  for (size_t i = 0; i < x_change.size(); i++) {
    bool is_opposite_color_adjacent = false;
    int x = x_tile_coordinate_;
    int y = y_tile_coordinate_;

    for (int j = 0; j < kBoardSize; j++) {
      x += x_change[i];
      y += y_change[i];

      if (!InBounds(x, y)) {
        break;
      }
      if (game_board[x][y].empty()) { // Checks for empty string
        break;
      } else if (game_board[x][y] != last_turn_color) {
        is_opposite_color_adjacent = true;
      } else if (is_opposite_color_adjacent) {
        return true;
      } else {
        break;
      }
    }
  }
  return false;
}

vector<pair<int, int>> MyApp::GetValidMoves() {
  vector<pair<int, int>> moves;
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      if (game_board[i][j].empty() && IsMoveValid(reinterpret_cast<int&>(i),
          reinterpret_cast<int&>(j))) {
        moves.emplace_back(i, j);
      }
    }
  }
  return moves;
}

bool MyApp::IsGameOver() {
  return (white_score + black_score == (kBoardSize * kBoardSize));
}

void MyApp::DrawScoresAndText() {
  const cinder::ivec2 size = {500, 50};
  const Color green = Color(board_r, board_g, board_b);
  const string white_score_text = "White: " + std::to_string(white_score);
  const string black_score_text = "Black: " + std::to_string(black_score);
  PrintText("Welcome to Othello!", green, size, vec2(860, 50));
  PrintText(white_score_text, green, size, vec2(860, 150));
  PrintText(black_score_text, green, size, vec2(860, 250));

  if (IsGameOver()) {
    string winner = GetWinner();
    if (winner == "tie") {
      leaderboard_.AddWinnerToScoreBoard("white", "black",
          white_score);
      PrintText("Game Over, it's a tie!", green, size,
                vec2(860, 350));
    } else {
      string loser = (winner == "white") ? "black" : "white";
      int winner_score = (winner == "white") ? white_score : black_score;
      leaderboard_.AddWinnerToScoreBoard(winner, loser, winner_score);
      PrintText("Game Over, " + winner + " wins!", green, size,
                vec2(860, 350));
    }
  }
}

string MyApp::GetWinner() {
  if (white_score > black_score) {
    return "white";
  } else if (white_score < black_score) {
    return "black";
  }
  return "tie";
}

void MyApp::PlaySound(const string& voice) {
  if (voice == "click") {
    audio::SourceFileRef source_file =
        audio::load( app::loadAsset( "click.wav"));
    move_voice = audio::Voice::create(source_file);
    // Start playing sound audio from file:
    move_voice->start();
  } else if (voice == "game over") {
    audio::SourceFileRef over_source_file =
        audio::load( app::loadAsset( "game_over.wav"));
    game_over_voice = audio::Voice::create(over_source_file);
    // Start playing sound audio from file:
    game_over_voice->start();
  } else {
    audio::SourceFileRef source_file =
        audio::load( app::loadAsset( "background.mp3"));
    music_voice = audio::Voice::create(source_file);
    // Start playing background music audio from file:
    music_voice->start();
  }
}

void MyApp::ResetGame() {
  white_score = 2;
  black_score = 2;
  game_board.clear();
  SetGameBoard();
  is_white_turn_ = false;
  valid_moves.clear();
}

void MyApp::SetGameBoard() {
  // Fills game board with empty strings initially
  vector<string> v(8, "");
  for (size_t i = 0; i < 8; i++) {
    game_board.push_back(v);
  }
  // Sets the starting 4 pieces in the middle of the board to white and black
  game_board[3][3] = "white";
  game_board[3][4] = "black";
  game_board[4][3] = "black";
  game_board[4][4] = "white";
}

}  // namespace myapp
