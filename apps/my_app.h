// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/Color.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <mylibrary/scoreboard.h>
#include <cinder/audio/Voice.h>
#include <string>
#include <cinder/app/App.h>
#include <sqlite_modern_cpp.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

using std::vector;
using std::string;
using std::pair;
using std::cout;
using std::endl;
using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using std::string;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using namespace ci;
using namespace ci::app;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  /**
   *
   */
  MyApp();

  /**
   *
   */
  void setup() override;

  /**
   *
   */
  void update() override;

  /**
   *
   */
  void draw() override;

  /**
   *
   */
  void mouseDown(cinder::app::MouseEvent) override;

 private:
  void FlipPieces(int& x_tile_coordinate_, int& y_tile_coordinate_);
  bool IsMoveValid(int& x_tile_coordinate_, int& y_tile_coordinate_);
  void DrawBoard();
  void UpdateScores();
  bool InBounds(int x, int y);
  bool IsGameOver();
  void DrawScoresAndText();
  static void PlaySound(const string& voice);
  void ResetGame();
  string GetWinner();
  vector<pair<int, int>> GetValidMoves();
  void SetGameBoard();
  void EndGameAndAddToLeaderBoard();
  othello::Scoreboard leaderboard_;
  cinder::gl::Texture2dRef background_;
  cinder::gl::Texture2dRef reset_;
  vector<vector<string>> game_board;
  bool is_white_turn_ = false;
  int black_score = 2;
  int white_score = 2;
  vector<pair<int, int>> valid_moves;
  const int kBoardSize = 8;
  const int kBoardBounds = 720;
  const int kTileLength = getWindowBounds().getHeight()/kBoardSize;
  const int kTileCenter = kTileLength/2;
  const int kCirclePieceRadius = 35;
  const float kBoardRed = 46.0 / 255.0;
  const float kBoardGreen = 174.0 /255.0;
  const float kBoardBlue = 82.0 / 255.0;
  const vector<int> kXChange{-1, 0, 1, -1, 1, -1, 0, 1};
  const vector<int> kYChange{-1, -1, -1, 0, 0, 1, 1, 1};
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
