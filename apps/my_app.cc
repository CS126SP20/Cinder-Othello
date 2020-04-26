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
const char kNormalFont[] = "Arial";

const char kDbPath[] = "scoreboard.db";

using cinder::app::KeyEvent;

MyApp::MyApp(): leaderboard_{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  //leaderboard_.AddWinnerToScoreBoard("player1", "player2", 30);
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

  valid_moves = GetValidMoves();

  UpdateScores();

  background_ = gl::Texture2d::create(loadImage
      (loadAsset("othello_board.png")));

  audio::SourceFileRef sourceFile =
      audio::load( app::loadAsset( "background.mp3"));
  music_voice = audio::Voice::create(sourceFile);
  // Start playing background music audio from file:
  music_voice->start();
}

void MyApp::update() {
  if (!music_voice->isPlaying()) { // If the music ended, repeat the music
    music_voice->start();
  }
}

void MyApp::draw() {
  gl::clear();
  gl::draw(background_, getWindowBounds());// Draws the game board
  DrawBoard();

  gl::color(Color(1,1,1));


}

void MyApp::keyDown(KeyEvent event) { }

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
      .alignment(TextBox::CENTER)
      .font(cinder::Font(kNormalFont, 30))
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


  vec2 center = getWindowCenter();
//  int r = 45;
//  float radius = 35;
  //int kTileLength = 90;




//  for (size_t i = 0; i < 4; i++) {
//
//    gl::color( Color( 1, 1, 1 ) ); // white
//    gl::drawSolidCircle( center + vec2( i*kTileLength + r, r ), radius );
//
//  }
//
//  for (size_t j = 0; j < 4; j++) {
//    gl::color( Color( 1, 1, 1 ) ); // white
//    gl::drawSolidCircle( center + vec2( r, j*kTileLength + r ), radius );
//  }

//  gl::drawSolidCircle( center + vec2( kTileLength + r, -2*kTileLength + r ), radius );
//  gl::drawSolidCircle( center + vec2( kTileLength + r, -3*kTileLength + r ), radius );
//  gl::drawSolidCircle( center + vec2( kTileLength + r, -4*kTileLength + r ), radius );
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

  for (size_t i = 0; i < valid_moves.size(); i++) {
    int xPos = valid_moves[i].first * kTileLength + kTileCenter;
    int yPos = valid_moves[i].second * kTileLength + kTileCenter;
    if (is_white_turn_) {
      gl::color(Color(1,1,1));
    } else {
      gl::color(Color(0,0,0));
    }
    gl::drawStrokedCircle(vec2(xPos, yPos), kCirclePieceRadius);
  }

}

void MyApp::mouseDown(cinder::app::MouseEvent event) {

//  float radius = 35;
//  int kTileSize = 90;
//  int r = 45;
//  int kTileX = 0;
//  int kTileY = 0;
  int x_tile_coordinate_ = event.getX();
  int y_tile_coordinate_ = event.getY();

  // The two lines below divide the x and y coordinates on the board by
  // 90 (pixel length of each square) to get the corresponding x and y
  // coordinates on the board (0 to 7)
  x_tile_coordinate_ = x_tile_coordinate_ / kTileLength;
  y_tile_coordinate_ = y_tile_coordinate_ / kTileLength;

//  is_white_turn_ = !is_white_turn_;
  if (IsMoveValid(x_tile_coordinate_, y_tile_coordinate_)) {
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
  }




//  vec2 center = getWindowCenter();
//  std::cout << event.getX() << std::endl;
//  std::cout << event.getY() << std::endl;
//  if (event.getY() < 90 && event.getX() < 90) {
//    std::cout << "true" << std::endl;
//    std::cout << 97/90 << std::endl; // divide the x-coordinate by 90 to get the x coordinate of the tile and the same for y
//    gl::color(Color(1,1,1));
//    gl::drawSolidCircle( vec2(kTileX * kTileSize + r, kTileY * kTileSize + r), radius);
//  }
}

void MyApp::FlipPieces(int& x_tile_coordinate_, int& y_tile_coordinate_) {
  string last_turn_color = "black";
  if (is_white_turn_) {
    last_turn_color = "white";
  }
//  prints the board
//  for (int i = 0; i < 8; i++) {
//    for (int j = 0; j < 8; j++) {
//      if (game_board[j][i].empty()) {
//        std::cout << "space ";
//      } else {
//        std::cout << game_board[j][i] + " ";
//      }
//    }
//    std::cout << std::endl;
//  }
//  std::cout << std::endl;


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
      if (game_board[i][j].empty() && IsMoveValid(reinterpret_cast<int&>(i), reinterpret_cast<int&>(j))) {
        moves.emplace_back(i, j);
      }
    }
  }
  return moves;
}

}  // namespace myapp
