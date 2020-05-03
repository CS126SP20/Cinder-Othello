//
// Created by Kaahan Motwani on 4/28/20.
//

#include "mylibrary/logic.h"

namespace logic {

vector<vector<string>> FlipPieces(int& x_tile_coordinate_,
    int& y_tile_coordinate_, bool is_white_turn_,
    vector<vector<string>> game_board_) {
  string last_turn_color = "black";
  if (is_white_turn_) {
    last_turn_color = "white";
  }
  vector<pair<int, int>> to_flip;

  for (size_t i = 0; i < kXChange.size(); i++) {
    int x = x_tile_coordinate_;
    int y = y_tile_coordinate_;

    for (size_t j = 0; j < kBoardSize; j++) {
      x += kXChange[i];
      y += kYChange[i];
      if (!InBounds(x, y)) {
        break;
      }

      if (game_board_[x][y].empty()) { // Checks for empty string
        break;
      } else if (game_board_[x][y] != last_turn_color) {
        to_flip.emplace_back(x, y); // Adds the pair of coordinates to to_flip
      } else { // == lastTurnColor
        for (const auto& pair : to_flip) {
          game_board_[pair.first][pair.second] = last_turn_color;
        }
        break;
      }
    }
    to_flip.clear();
  }

  return game_board_;
}

bool InBounds(int x, int y) {
  return (x >= 0) && (x < kBoardSize) && (y >= 0) && (y < kBoardSize);
}

bool IsMoveValid(int& x_tile_coordinate_, int& y_tile_coordinate_,
                 bool is_white_turn_, vector<vector<string>>& game_board_) {
  if (!InBounds(x_tile_coordinate_, y_tile_coordinate_)) {
    return false;
  }
  string last_turn_color = "black";
  if (is_white_turn_) {
    last_turn_color = "white";
  }
  // If there's already a piece at that spot on the board, it is not
  // possible for it to be a valid move.
  if (!game_board_[x_tile_coordinate_][y_tile_coordinate_].empty()) {
    return false;
  }

  for (size_t i = 0; i < kXChange.size(); i++) {
    bool is_opposite_color_adjacent = false;
    int x = x_tile_coordinate_;
    int y = y_tile_coordinate_;

    for (size_t j = 0; j < kBoardSize; j++) {
      x += kXChange[i];
      y += kYChange[i];
      if (!InBounds(x, y)) {
        break;
      }

      if (game_board_[x][y].empty()) { // Checks for empty string
        break;
      } else if (game_board_[x][y] != last_turn_color) {
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

vector<pair<int, int>> GetValidMoves(vector<vector<string>>& game_board_,
    bool is_white_turn_) {
  vector<pair<int, int>> moves;
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      if (game_board_[i][j].empty() && IsMoveValid
      (reinterpret_cast<int&>(i), reinterpret_cast<int&>(j),
          is_white_turn_, game_board_)) {
        moves.emplace_back(i, j);
      }
    }
  }
  return moves;
}

}