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

const char kNormalFont[] = "Arial";

const char kDbPath[] = "scoreboard.db";

using cinder::app::KeyEvent;

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

MyApp::MyApp(): leaderboard_{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() {
  leaderboard_.AddWinnerToScoreBoard("player1", "player2", 30);
  //cinder::gl::drawLine();


  background_ = gl::Texture2d::create(loadImage(loadAsset("othello_board.png")));

//  Surface processedImage(( loadImage( loadResource("othello_board.JPG" ) ) ) );
//  background_ = gl::Texture2d::create( processedImage );
}

void MyApp::update() { }

void MyApp::draw() {
  //cinder::ip::checkerboard(8, 8, 100, Color::black(), Color::black());

  //background_ = gl::Texture2d::create(loadImage(loadAsset("othello_board.png")));

  // and in your App's draw()
  gl::draw(background_, getWindowBounds());

  vec2 center = getWindowCenter();
  float r = 50;
  float radius = 40;

  gl::color( Color( 1, 1, 1 ) ); // black
  gl::drawSolidCircle( center + vec2( r, r ), radius );
  gl::color( Color( 1, 1, 1 ) );
  gl::drawSolidCircle( center + vec2( -r, -r ), radius );
  gl::color( Color( 0, 0, 0 ) ); // white
  gl::drawSolidCircle( center + vec2( -r, r), radius );
  gl::color( Color( 0, 0, 0 ) );
  gl::drawSolidCircle( center + vec2( r, -r), radius );

//  const Color color = Color::black();
  //const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  PrintText("Game Over :(", Color::white(), size, center);
}

void MyApp::keyDown(KeyEvent event) { }



}  // namespace myapp
