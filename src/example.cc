// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/example.h>

namespace othello {

 Scoreboard::Scoreboard(const std::string& db_path) : db_{db_path} {
    db_ << "CREATE TABLE if not exists scoreboard (\n"
           "  winner  TEXT NOT NULL,\n"
           "  loser  TEXT NOT NULL,\n"
           "  score INTEGER NOT NULL\n"
           ");";
  }
}  // namespace mylibrary
