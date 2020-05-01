# **C++ Othello**

![](assets/game_image.png)

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

**Author**: Kaahan Motwani - [`kaahanm2@illinois.edu`](mailto:example@illinois.edu)

---

### **Table of Contents**
- [Getting Started](#getting-started)
    - 
    - [Downloading Cinder](#downloading-cinder)
    - [Setting up the SQLite Database](#setting-up-the-sqlitehttpswwwsqliteorgindexhtml-database)

### **Getting Started**

#### Downloading Cinder ####

1. Download [Cinder (v0.9.2)](https://libcinder.org/) for your platform. 
Extract the downloaded item into a folder. 
We’ll call this folder ~/Cinder throughout the instructions.

2. If you do not have the [CLion](https://www.jetbrains.com/clion/) IDE, 
download it. CLion comes with [CMake](https://cmake.org/) and since this 
is a CMake Project, you will need CMake to run the project.

2. Open the ~/Cinder folder into the CLion IDE (and click the green build button. 
This will build libcinder. You only need to do this once 
per machine. This build might take a while.

3. Create a directory, say my-projects in ~/Cinder. 
Clone the C++ Othello project into this folder.

4. Open the snake project in CLion, set the target to 
cinder-snake and click the run button.

MacOS users: It’s possible that you may come across:

```
Error running 'cinder-final-project': Cannot run program … cinder-final-project.app/Contents/Resources"): error=13, Permission denied
```

In this case, try doing: Edit configurations -> Executable -> Select Other -> Find ```my-projects/final-project/cmake-build-debug/Debug/cinder-final-project/Contents/MacOS/cinder-final-project``` And click run once again.

#### Setting up the [SQLite](https://www.sqlite.org/index.html) Database ####

1. In CLion, navigate to View > Tool Windows > Database.
2. Next, in the Database window, select the Database properties button, which is between the Refresh and the Stop button.
3. There are two possibilities now: i. If properties for snake.db are automatically selected, you can proceed to Step 4. ii. If there are no database properties selected, navigate to Add > SQLite.
4. Next, there should be a highlighted link to download the necessary drivers for SQLite. Click this link.
5. For the file of the datasource, select final-project-kaahanmotwani/assets/snake.db.
6. Press Test Connection to verify that the driver is set up correctly. Click the OK button in the
7. Now, you should run the cinder-snake target and play the game to test out your database.
8. After the cinder-snake application has run, go back to the Database tab, click the Refresh button. You should now be able to see the schema of the database under snake.db > schemas > main > scoreboard. Also, you’ll be able to manually execute queries by clicking the Jump to Console button at the top.

#### Adding the SQLite dependencies ####

In final-project-kaahanmotwani/CMakeLists.txt:

``` 
FetchContent_Declare(
        sqlite-modern-cpp
        GIT_REPOSITORY https://github.com/SqliteModernCpp/sqlite_modern_cpp.git
        GIT_TAG a0f96c10f04d96ccea1b8a49d5998c96e7887bf4
)
```

This will download a Git repository into your build folder. The first argument is the name that you want to refer to the entity as.

Then add the following to final-project-kaahanmotwani/CMakeLists.txt:

```
FetchContent_GetProperties(sqlite-modern-cpp)
if (NOT sqlite-modern-cpp_POPULATED)
    FetchContent_Populate(sqlite-modern-cpp)
    add_library(sqlite-modern-cpp INTERFACE)
    target_include_directories(sqlite-modern-cpp INTERFACE ${sqlite-modern-cpp_SOURCE_DIR}/hdr)
endif ()
```

This will add the dependency for [sqlite_modern_cpp](https://github.com/SqliteModernCpp/sqlite_modern_cpp)
We are using the SqliteModernCpp library to make SQLite queries from C++. Take a look at the examples here: https://github.com/SqliteModernCpp/sqlite_modern_cpp/tree/dev.
Then, you'll do something like this, still in final-project-<github-name>/CMakeLists.txt:

FetchContent_GetProperties(gflags)
if(NOT gflags_POPULATED)
    FetchContent_Populate(gflags)
    add_subdirectory(${gflags_SOURCE_DIR} ${gflags_BINARY_DIR})
endif()
Notice that gflags is a CMake project, so you can add it as a subdirectory of your project. This piece of code adds gflags as a subdirectory of your project, which will expose any targets that gflags defines.

NOTE: It is important that your variable names are all lowercase for FetchContent. The FetchContent_Populate(<name>) method will convert <name> into lowercase, so just make all of the names lowercase. See more here: https://cmake.org/pipermail/cmake/2018-March/067185.html.