// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/scoreboard.h>
#include <catch2/catch.hpp>
#include <mylibrary/logic.h>

using std::vector;
using std::pair;

TEST_CASE("Random sanity test", "[random]") {
  vector<vector<string>> starting_board;
  vector<string> v(8, "");
  for (size_t i = 0; i < 8; i++) {
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
}