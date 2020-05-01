// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/scoreboard.h>
#include <catch2/catch.hpp>
#include <mylibrary/logic.h>

using std::vector;
using std::pair;

TEST_CASE("Random sanity test", "[random]") {
  const int kBoardSize = 8;
  vector<vector<string>> starting_board;
  vector<string> v(kBoardSize, "");
  for (size_t i = 0; i < kBoardSize; i++) {
    starting_board.push_back(v);
  }
  starting_board[3][3] = "white";
  starting_board[3][4] = "black";
  starting_board[4][3] = "black";
  starting_board[4][4] = "white";

  vector<pair<int, int>> valid_moves;
  valid_moves.emplace_back(2, 3);
  valid_moves.emplace_back(3, 2);
  valid_moves.emplace_back(4, 5);
  valid_moves.emplace_back(5, 4);

  REQUIRE(logic::GetValidMoves(starting_board, false) == valid_moves);

  SECTION("full board") {

    for (size_t i = 0; i < kBoardSize; i++) {
      for (size_t j = 0; j < kBoardSize; j++) {
        if (i % 2 == 0) {
          starting_board[j][i] = "white";
        } else {
          starting_board[j][i] = "black";
        }
      }
    }
    valid_moves.clear();
    REQUIRE(logic::GetValidMoves(starting_board, false) == valid_moves);
  }
}