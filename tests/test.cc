// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/scoreboard.h>
#include <catch2/catch.hpp>
#include <mylibrary/logic.h>

using std::vector;
using std::pair;
using std::map;
using std::string;
using std::make_pair;

const int kBoardSize = 8;

vector<vector<string>> FillGameBoard(const map<pair<int, int>, string>&
    coord_to_color_map) {
  vector<vector<string>> game_board;
  vector<string> v(kBoardSize, "");
  // Fills the game board with all empty strings initially
  for (size_t i = 0; i < kBoardSize; i++) {
    game_board.push_back(v);
  }
  for (const auto& coord_to_color : coord_to_color_map) {
    game_board[coord_to_color.first.first][coord_to_color.first.second]
      = coord_to_color.second;
  }

  return game_board;
}

TEST_CASE("Valid moves can be found", "[valid-moves]") {
  map<pair<int, int>, string> coord_to_color_map
      = {{make_pair(3, 3), "white"},
         {make_pair(3, 4), "black"},
         {make_pair(4, 3), "black"},
         {make_pair(4, 4), "white"}};
  
  vector<vector<string>> game_board = FillGameBoard(coord_to_color_map);
//  vector<vector<string>> starting_board;
//  vector<string> v(kBoardSize, "");
//  for (size_t i = 0; i < kBoardSize; i++) {
//    starting_board.push_back(v);
//  }
//
//  starting_board[3][3] = "white";
//  starting_board[3][4] = "black";
//  starting_board[4][3] = "black";
//  starting_board[4][4] = "white";

  vector<pair<int, int>> valid_moves;
  valid_moves.emplace_back(2, 3);
  valid_moves.emplace_back(3, 2);
  valid_moves.emplace_back(4, 5);
  valid_moves.emplace_back(5, 4);

  REQUIRE(logic::GetValidMoves(game_board, false) == valid_moves);

//  SECTION("full board") {
//    for (size_t i = 0; i < kBoardSize; i++) {
//      for (size_t j = 0; j < kBoardSize; j++) {
//        if (i % 2 == 0) {
//          starting_board[j][i] = "white";
//        } else {
//          starting_board[j][i] = "black";
//        }
//      }
//    }
//    valid_moves.clear();
//    REQUIRE(logic::GetValidMoves(starting_board, false) == valid_moves);
//  }
}

TEST_CASE("Pieces on the game board can be flipped", "[flip-pieces]") {
  map<pair<int, int>, string> coord_to_color_map
    = {{make_pair(3, 2), "black"},
     {make_pair(3, 3), "black"},
     {make_pair(3, 4), "black"},
     {make_pair(4, 3), "black"},
     {make_pair(4, 4), "white"},
     {make_pair(2, 2), "white"}};
  vector<vector<string>> starting_board = FillGameBoard(coord_to_color_map);
//  vector<string> v(kBoardSize, "");
//  for (size_t i = 0; i < kBoardSize; i++) {
//    starting_board.push_back(v);
//  }
//  starting_board[3][2] = "black";
//  starting_board[3][3] = "black";
//  starting_board[3][4] = "black";
//  starting_board[4][3] = "black";
//  starting_board[4][4] = "white";
//  starting_board[2][2] = "white";

  // Creates the game board with the same pieces (before any flips)
  vector<vector<string>> expected_game_board = starting_board;
  // This is the piece that should flip to white if the last move was (2, 2)
  expected_game_board[3][3] = "white";
  int x_move = 2;
  int y_move = 2;

  REQUIRE(logic::FlipPieces(x_move, y_move, true, starting_board)
          == expected_game_board);
}

TEST_CASE("In bounds", "[in-bounds]") {
  REQUIRE(logic::InBounds(4, 4)); // Checks for in-bounds coordinates
  REQUIRE(!logic::InBounds(9, 1)); // Checks for out-of-bounds coordinates
}