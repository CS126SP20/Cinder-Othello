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
#include <mylibrary/logic.h>

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
using std::to_string;
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

  /**
   *
   */
  void mouseMove(cinder::app::MouseEvent) override;

 private:

  /**
   *
   */
  void DrawBoard();

  /**
   *
   */
  void UpdateScores();

  /**
   *
   * @return
   */
  bool IsGameOver();

  /**
   *
   */
  void DrawScoresAndText();

  /**
   *
   * @return
   */
  string GetWinner();

  /**
   *
   */
  static void PlaySound(const string& voice);

  /**
   *
   */
  void ResetGame();

  /**
   *
   */
  void SetInitialGameBoard();

  /**
   *
   */
  void EndGameAndAddToLeaderboard();

 private:
  othello::Scoreboard leaderboard_;
  cinder::gl::Texture2dRef background_;
  cinder::gl::Texture2dRef reset_;
  vector<vector<string>> game_board_;
  vector<pair<int, int>> valid_moves_;
  bool is_white_turn_ = false;
  int black_score_ = 2;
  int white_score_ = 2;
  const int kPanelCenterX = 860; // The center x-coord of the game's panel
  // The following four constants represent the y coordinates of places where
  // messages are printed in the panel for the user
  const int kTurnY = 100;
  const int kWhiteScoreY = 200;
  const int kBlackScoreY = 300;
  const int kGameOverY = 400;
  const int kBoardSize = 8;
  const int kBoardBounds = getWindowBounds().getHeight();
  const int kTileLength = getWindowBounds().getHeight() / kBoardSize;
  const int kTileCenter = kTileLength/2;
  const int kCirclePieceRadius = 35;
  // The rgb values to get a green color matching the color of the game board
  const float kBoardRed = 46.0 / 255.0;
  const float kBoardGreen = 174.0 / 255.0;
  const float kBoardBlue = 82.0 / 255.0;
  const int kFirstStartCoord = 3;
  const int kSecondStartCoord = 4;
  // These vectors represent the 8 directions on the Othello board in
  // which a piece can move; used to show valid moves to the players
  const vector<int> kXChange{-1, 0, 1, -1, 1, -1, 0, 1};
  const vector<int> kYChange{-1, -1, -1, 0, 0, 1, 1, 1};
  // Potential game board acts as the game board if the user was to play a
  // move. They are able to see what happens when they hover over a valid move.
  vector<vector<string>> potential_game_board_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
