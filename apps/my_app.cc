// Copyright (c) 2020 Kaahan Motwani. All rights reserved.

#include "my_app.h"

namespace myapp {

audio::VoiceRef music_voice;
audio::VoiceRef move_voice;
audio::VoiceRef game_over_voice;
const char kNormalFont[] = "Arial";
const char kDbPath[] = "scoreboard.db";

MyApp::MyApp(): leaderboard_{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  SetInitialGameBoard();
  valid_moves_ = logic::GetValidMoves(game_board_, is_white_turn_);
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
    const Rectf reset_bounds(810, 450, 910, 550);
    gl::draw(reset_, reset_bounds);// Draws the reset button
  }
  DrawBoard();
  DrawScoresAndText();
  gl::color(Color(1,1,1));
}

void MyApp::mouseDown(cinder::app::MouseEvent event) {
  if (IsGameOver() && event.getX() >= 810 && event.getX() <= 910
      && event.getY() >= 450 && event.getY() <= 550) {
    ResetGame();
  }
  int x_tile_coordinate_ = event.getX();
  int y_tile_coordinate_ = event.getY();

  // The two lines below divide the x and y coordinates on the board by
  // 90 (pixel length of each square) to get the corresponding x and y
  // coordinates on the board (0 to 7)
  x_tile_coordinate_ = x_tile_coordinate_ / kTileLength;
  y_tile_coordinate_ = y_tile_coordinate_ / kTileLength;

  if (logic::IsMoveValid(x_tile_coordinate_, y_tile_coordinate_,
      is_white_turn_, game_board_)) {
    PlaySound("click");
    valid_moves_.clear();
    if (is_white_turn_) {
      game_board_[x_tile_coordinate_][y_tile_coordinate_] = "white";
    } else {
      game_board_[x_tile_coordinate_][y_tile_coordinate_] = "black";
    }

    game_board_ = logic::FlipPieces(x_tile_coordinate_,
        y_tile_coordinate_, is_white_turn_, game_board_);
    UpdateScores();
  } else {
    is_white_turn_ = !is_white_turn_;
  }
  is_white_turn_ = !is_white_turn_;
  valid_moves_ = logic::GetValidMoves(game_board_, is_white_turn_);

  if (valid_moves_.empty()) {
    is_white_turn_ = !is_white_turn_;
    valid_moves_ = logic::GetValidMoves(game_board_, is_white_turn_);
  }

  if (IsGameOver()) {
    EndGameAndAddToLeaderboard();
  }
}

void MyApp::mouseMove(MouseEvent event) {
  int x_pos = event.getX();
  int y_pos = event.getY();
  x_pos = x_pos / kTileLength;
  y_pos = y_pos / kTileLength;

  // Fills the potential game board with empty strings every time the mouse
  // moves. If the user hovers over a valid move, then the appropriate pieces
  // in potential game board will be filled to show what the game board
  // would look like if they moved there.
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      potential_game_board_[j][i] = "";
    }
  }

  if (logic::IsMoveValid(x_pos, y_pos, is_white_turn_,
      game_board_)) {
    // The whole game board if they were to click on this piece
    potential_game_board_ = logic::FlipPieces(x_pos, y_pos,
        is_white_turn_, game_board_);

    // This if-else block turns the current tile that the user is on into
    // white or black if it's a valid move
    if (is_white_turn_) {
      potential_game_board_[x_pos][y_pos] = "white";
    } else {
      potential_game_board_[x_pos][y_pos] = "black";
    }
  }
}

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
  const cinder::vec2 locp = {loc.x - box_size.x / 2,
                             loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::DrawBoard() {
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      int xPos = i * kTileLength + kTileCenter;
      int yPos = j * kTileLength + kTileCenter;
      if (game_board_[i][j] == "white") {
        gl::color(Color(1,1,1));
        gl::drawSolidCircle( vec2(xPos, yPos), kCirclePieceRadius);
      } else if (game_board_[i][j] == "black") {
        gl::color(Color(0,0,0));
        gl::drawSolidCircle( vec2(xPos, yPos), kCirclePieceRadius);
      }

      if (potential_game_board_[i][j] == "white") {
        gl::color(Color(1,1,1));
        gl::drawSolidCircle( vec2(xPos, yPos), kCirclePieceRadius);
      } else if (potential_game_board_[i][j] == "black") {
        gl::color(Color(0,0,0));
        gl::drawSolidCircle( vec2(xPos, yPos), kCirclePieceRadius);
      }

    }
  }

  for (auto& valid_move : valid_moves_) {
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

void MyApp::UpdateScores() {
  white_score_ = 0;
  black_score_ = 0;
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      if (game_board_[j][i] == "white") {
        white_score_++;
      } else if (game_board_[j][i] == "black") {
        black_score_++;
      }
    }
  }
}

bool MyApp::IsGameOver() {
  return (white_score_ + black_score_ == (kBoardSize * kBoardSize));
}

void MyApp::DrawScoresAndText() {
  const cinder::ivec2 kBoxSize = {500, 50};
  const Color kGreen = Color(kBoardRed, kBoardGreen, kBoardBlue);
  const string white_score_text = "White: " + to_string(white_score_);
  const string black_score_text = "Black: " + to_string(black_score_);
  PrintText("Welcome to Othello!",
      kGreen, kBoxSize, vec2(860, 50));
  PrintText(white_score_text, kGreen, kBoxSize, vec2(860, 200));
  PrintText(black_score_text, kGreen, kBoxSize, vec2(860, 300));
  string turn = is_white_turn_ ? "White" : "Black";
  PrintText(turn + " Turn", kGreen, kBoxSize,
            vec2(860, 100));

  if (IsGameOver()) {
    string winner = GetWinner();
    if (winner == "tie") {
      PrintText("Game Over, it's a tie!", kGreen, kBoxSize,
                vec2(860, 400));
    } else {
      PrintText("Game Over, " + winner + " wins!", kGreen, kBoxSize,
                vec2(860, 400));
    }
  }
}

string MyApp::GetWinner() {
  if (white_score_ > black_score_) {
    return "white";
  } else if (white_score_ < black_score_) {
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
  white_score_ = 2;
  black_score_ = 2;
  game_board_.clear();
  SetInitialGameBoard();
  is_white_turn_ = false;
  valid_moves_ = logic::GetValidMoves(game_board_, is_white_turn_);
}

void MyApp::SetInitialGameBoard() {
  // Fills game board and potential game board with empty strings initially
  vector<string> v(kBoardSize, "");
  for (size_t i = 0; i < kBoardSize; i++) {
    game_board_.push_back(v);
    potential_game_board_.push_back(v);
  }
  // Sets the starting 4 pieces in the middle of the board to white and black
  game_board_[kFirstStartCoord][kFirstStartCoord] = "white";
  game_board_[kFirstStartCoord][kSecondStartCoord] = "black";
  game_board_[kSecondStartCoord][kFirstStartCoord] = "black";
  game_board_[kSecondStartCoord][kSecondStartCoord] = "white";
}

void MyApp::EndGameAndAddToLeaderboard() {
  string winner = GetWinner();
  PlaySound("game over");
  if (winner == "tie") {
    leaderboard_.AddWinnerToScoreBoard("tie", "tie",
                                       white_score_);
  } else {
    string loser = (winner == "white") ? "black" : "white";
    int winner_score = (winner == "white") ? white_score_ : black_score_;
    leaderboard_.AddWinnerToScoreBoard(winner, loser, winner_score);
  }
}

}  // namespace myapp
