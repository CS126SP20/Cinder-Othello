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
    - [Downloading Cinder](#downloading-cinder)

### **Getting Started**

#### Downloading Cinder ####

1. Download [Cinder (v0.9.2)](https://libcinder.org/) for your platform. 
Extract the downloaded item into a folder. 
We’ll call this folder ~/Cinder throughout the instructions.

2. Open the ~/Cinder folder into the [CLion](https://www.jetbrains.com/clion/) IDE (download it if you 
do not have it) and click the green build button. 
This will build libcinder. You only need to do t
his once per machine. This build might take a while.

3. Create a directory, say my-projects in ~/Cinder. 
Clone the C++ Othello project into this folder.

4. Open the snake project in CLion, set the target to 
cinder-snake and click the run button.

MacOS users: It’s possible that you may come across:

```xml
Error running 'cinder-final-project': Cannot run program … cinder-final-project.app/Contents/Resources"): error=13, Permission denied
```

In this case, try doing: Edit configurations -> Executable -> Select Other -> Find ```my-projects/final-project/cmake-build-debug/Debug/cinder-final-project/Contents/MacOS/cinder-final-project``` And click run once again.

#### Setting up the [SQLite](https://www.sqlite.org/index.html) Database ####

1. In CLion, navigate to View > Tool Windows > Database.
2. Next, in the Database window, select the Database properties button, which is between the Refresh and the Stop button.
3. There are two possibilities now: i. If properties for snake.db are automatically selected, you can proceed to Step 4. ii. If there are no database properties selected, navigate to Add > SQLite.
4. Next, there should be a highlighted link to download the necessary drivers for SQLite. Click this link.
5. For the file of the datasource, select snake-<your-netid>/assets/snake.db.
6. Press Test Connection to verify that the driver is set up correctly. Click the OK button in the
7. Now, you should run the cinder-snake target and play the game to test out your database.
8. After the cinder-snake application has run, go back to the Database tab, click the Refresh button. You should now be able to see the schema of the database under snake.db > schemas > main > leaderboard. Also, you’ll be able to manually execute queries by clicking the Jump to Console button at the top.