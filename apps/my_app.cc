// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <sqlite_modern_cpp.h>


namespace myapp {

const char kDbPath[] = "scoreboard.db";

using cinder::app::KeyEvent;

MyApp::MyApp(): leaderboard_{cinder::app::getAssetPath(kDbPath).string()} {}

void MyApp::setup() { }

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
