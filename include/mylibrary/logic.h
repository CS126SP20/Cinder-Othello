//
// Created by Kaahan Motwani on 4/28/20.
//

#ifndef FINALPROJECT_LOGIC_H
#define FINALPROJECT_LOGIC_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::pair;

namespace logic {

/**
   *
   * @param x_tile_coordinate_
   * @param y_tile_coordinate_
   */
vector<vector<string>> FlipPieces(int& x_tile_coordinate_,
                                  int& y_tile_coordinate_, bool& is_white_turn_,
                                  vector<vector<string>>& game_board_);

/**
 *
 * @param x
 * @param y
 * @return
 */
bool InBounds(int x, int y);

pair<int, int> UpdateScores(vector<vector<string>>& game_board_,
                                    int& white_score_, int& black_score_);

bool IsMoveValid(int& x_tile_coordinate_, int& y_tile_coordinate_,
    bool& is_white_turn_, vector<vector<string>>& game_board_);

vector<pair<int, int>> GetValidMoves(vector<vector<string>>& game_board_,
                                     bool is_white_turn_);

// These vectors represent the 8 directions on the Othello board in
// which a piece can move; used to show valid moves to the players
const vector<int> kXChange{-1, 0, 1, -1, 1, -1, 0, 1};
const vector<int> kYChange{-1, -1, -1, 0, 0, 1, 1, 1};
const int kBoardSize = 8;

}

#endif  // FINALPROJECT_LOGIC_H
