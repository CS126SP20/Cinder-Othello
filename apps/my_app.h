// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/Color.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/scoreboard.h>

#include <string>

using std::vector;
using std::string;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

 private:
  void drawPieceOnClick();
  void flipPieces();
  othello::Scoreboard leaderboard_;
  cinder::gl::Texture2dRef background_;
  vector<vector<string>> game_board;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
