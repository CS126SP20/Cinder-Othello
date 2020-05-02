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
const bool is_white_turn = false;

/**
 *
 *
 * @param coord_to_color_map
 * @return
 */
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

/**
 *
 *
 * @param game_board
 * @return
 */
vector<vector<string>> GetFullBoard(vector<vector<string>>& game_board) {
  // Fills the entire game board with black or white
  for (size_t i = 0; i < kBoardSize; i++) {
    for (size_t j = 0; j < kBoardSize; j++) {
      if (i % 2 == 0) {
        game_board[j][i] = "white";
      } else {
        game_board[j][i] = "black";
      }
    }
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

  vector<pair<int, int>> valid_move_coords;
  valid_move_coords.emplace_back(2, 3);
  valid_move_coords.emplace_back(3, 2);
  valid_move_coords.emplace_back(4, 5);
  valid_move_coords.emplace_back(5, 4);

  SECTION("Find valid moves on a normal board") {
    REQUIRE(logic::GetValidMoves(game_board, false) == valid_move_coords);
  }

  SECTION("Find valid moves on a full board") {
    game_board = GetFullBoard(game_board);
    valid_move_coords.clear();
    REQUIRE(logic::GetValidMoves(game_board, false) == valid_move_coords);
  }
}

TEST_CASE("Pieces on the game board can be flipped", "[flip-pieces]") {
  map<pair<int, int>, string> coord_to_color_map
    = {{make_pair(3, 2), "black"},
     {make_pair(3, 3), "black"},
     {make_pair(3, 4), "black"},
     {make_pair(4, 3), "black"},
     {make_pair(4, 4), "white"},
     {make_pair(2, 2), "white"}};
  vector<vector<string>> game_board = FillGameBoard(coord_to_color_map);
  int x_move = 2;
  int y_move = 2;

  SECTION("Flip pieces on a normal board") {
    // {3, 3} should flip to white if the last move was {2, 2}
    coord_to_color_map[{3, 3}] = "white";
    vector<vector<string>> expected_game_board
      = FillGameBoard(coord_to_color_map);

    REQUIRE(logic::FlipPieces(x_move, y_move, true, game_board)
            == expected_game_board);
  }

  SECTION("Flip pieces with an invalid move") {
    x_move = 7;

    REQUIRE(logic::FlipPieces(x_move, y_move, true, game_board)
            == game_board);
  }

  SECTION("Flip pieces on a completely full board") {
    game_board = GetFullBoard(game_board);

    REQUIRE(logic::FlipPieces(x_move, y_move, is_white_turn, game_board)
            == game_board);
  }
}

TEST_CASE("Checks If Moves Are Valid", "[is-move-valid]") {
  map<pair<int, int>, string> coord_to_color_map
      = {{make_pair(3, 3), "white"},
         {make_pair(3, 4), "black"},
         {make_pair(4, 3), "black"},
         {make_pair(4, 4), "white"}};

  vector<vector<string>> game_board = FillGameBoard(coord_to_color_map);
  int x_move = 2;
  int y_move = 3;

  SECTION("Test for a Valid Move") {
    REQUIRE(logic::IsMoveValid(x_move, y_move, is_white_turn, game_board));
  }

  SECTION("Test for an Invalid Move") {
    y_move = 2;

    REQUIRE(!logic::IsMoveValid(x_move, y_move, is_white_turn, game_board));
  }

  SECTION("Test for when the board is completely full") {
    game_board = GetFullBoard(game_board);

    REQUIRE(!logic::IsMoveValid(x_move, y_move, is_white_turn, game_board));
  }
}

TEST_CASE("Checks if Coordinates Are In Bounds", "[in-bounds]") {
  int x_coord = 0;
  int y_coord = 0;

  SECTION("In Bounds Coordinates") {
    // Checks for in-bounds coordinates (x or y less than or equal to 7)
    REQUIRE(logic::InBounds(x_coord, y_coord));
  }

  SECTION("Out of Bounds Coordinates") {
    y_coord = 10;
    
    // Checks for out-of-bounds coordinates (x or y greater than 7)
    REQUIRE(!logic::InBounds(x_coord, y_coord));
  }
}