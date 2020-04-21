// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <sqlite_modern_cpp.h>

namespace othello {

class Scoreboard {
 public:
  // Creates a new leaderboard table if it doesn't already exist.
  explicit Scoreboard(const std::string& db_path);

 private:
  sqlite::database db_;
};

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
