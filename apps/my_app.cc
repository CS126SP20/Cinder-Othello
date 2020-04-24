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
  leaderboard_.AddWinnerToScoreBoard("player1", "player2", 30);
  // Fills game board with empty strings
  vector<string> v(8, "");

  for (size_t i = 0; i < 8; i++) {
    game_board.push_back(v);
  }
  // Sets the starting 4 pieces to white and black
  game_board[3][3] = "white";
  game_board[3][4] = "black";
  game_board[4][3] = "black";
  game_board[4][4] = "white";

  background_ = gl::Texture2d::create(loadImage
      (loadAsset("othello_board.png")));

  audio::SourceFileRef sourceFile =
      audio::load( app::loadAsset( "background.mp3"));
  music_voice = audio::Voice::create(sourceFile);
  // Start playing audio from file:
  music_voice->start();
}

void MyApp::update() {
  if (!music_voice->isPlaying()) {
    music_voice->start();
  }

  if (white_turn_) {
    r = 1;
    g = 1;
    b = 1;
  } else {
    r = 0;
    g = 0;
    b = 0;
  }

  //gl::color(Color(r,g,b));
}

void MyApp::draw() {

  DrawStartingBoard();

  gl::color(Color(1,1,1));

  //DrawPieceOnClick();

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

void MyApp::DrawStartingBoard() {
  // and in your App's draw()
  gl::draw(background_, getWindowBounds());

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
  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      if (game_board[i][j] == "white") {
        gl::color(Color(1,1,1));
        gl::drawSolidCircle( vec2(i * kTileLength + kTileCenter,
                                  j * kTileLength + kTileCenter), kCirclePieceRadius);
      } else if (game_board[i][j] == "black") {
        gl::color(Color(0,0,0));
        gl::drawSolidCircle( vec2(i * kTileLength + kTileCenter,
                                  j * kTileLength + kTileCenter), kCirclePieceRadius);
      }
    }
  }


//  gl::color( Color( 1, 1, 1 ) ); // white
//  gl::drawSolidCircle( center + vec2(kTileCenter, kTileCenter),
//      kCirclePieceRadius);
//  gl::color( Color( 1, 1, 1 ) );
//  gl::drawSolidCircle( center + vec2(-kTileCenter, -kTileCenter),
//      kCirclePieceRadius);
//  gl::color( Color( 0, 0, 0 ) ); // black
//  gl::drawSolidCircle( center + vec2(-kTileCenter, kTileCenter),
//      kCirclePieceRadius);
//  gl::color( Color( 0, 0, 0 ) );
//  gl::drawSolidCircle( center + vec2(kTileCenter, -kTileCenter),
//      kCirclePieceRadius);
}

void MyApp::DrawPieceOnClick() {
//  float radius = 35;
//  int kTileSize = 90;
//  int r = 45;
//  int kTileX = 0;
//  int kTileY = 0;
  vec2 center = getWindowCenter();


//  x_tile_coordinate_ = x_tile_coordinate_/kTileSize;
//  y_tile_coordinate_ = y_tile_coordinate_/kTileSize;

  for (size_t i = 0; i < 8; i++) {
    for (size_t j = 0; j < 8; j++) {
      if (game_board[i][j] == "white" || game_board[i][j] == "black") {
        gl::drawSolidCircle( vec2(i * kTileLength + kTileCenter,
            j * kTileLength + kTileCenter), kCirclePieceRadius);
      }
    }
  }

//  const cinder::vec2 center2 = getWindowCenter();
//  const cinder::ivec2 size = {500, 50};
//  PrintText("Game Over :(", Color::white(), size, center2);

}


void MyApp::FlipPieces() {

}

void MyApp::mouseDown(cinder::app::MouseEvent event) {

//  float radius = 35;
//  int kTileSize = 90;
//  int r = 45;
//  int kTileX = 0;
//  int kTileY = 0;
  x_tile_coordinate_ = event.getX();
  y_tile_coordinate_ = event.getY();
  x_tile_coordinate_ = x_tile_coordinate_/kTileLength;
  y_tile_coordinate_ = y_tile_coordinate_/kTileLength;

  white_turn_ = !white_turn_;
  if (white_turn_) {
    game_board[x_tile_coordinate_][y_tile_coordinate_] = "white";
//    r = 1;
//    g = 1;
//    b = 1;
  } else {
    game_board[x_tile_coordinate_][y_tile_coordinate_] = "black";
//    r = 0;
//    g = 0;
//    b = 0;
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

}  // namespace myapp
