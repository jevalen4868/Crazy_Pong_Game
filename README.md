# Welcome to Pong_Game

# Please enjoy with a friend!
* W is up and S is down for the left player.
* ARROW KEY UP is up and ARROW KEY DOWN is down for the right player.
* ESC will quit the game and ENTER will resume once a player has scored.
* The score is kept at the window title.

# IDE?
For windows, I recommend using visual studio, please see "To build for windows" section.
For linux, any editor would likely do.

# to execute on linux

## Dependencies for running on linux
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)

## Basic linux build instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

# To execute for windows

## Dependencies for running on windows.
* Latest version of visual studio community
* SDL2 > 2.0 - note where to place this in the build instructions.

## Basic windows build instructions.
1. Clone this repo.
2. Download and place SDL VS library in the cmake folder in the project root folder, i.e. cmake/SDL2-2.0.12, if your version differs, update the CMakeLists.txt file which sets the dir.
3. Create cmake-build-debug folder in project root folder.
4. Open Visual studio based commande line, cd into the cmake-build-debug folder and run "cmake .."
5. Run Build -> Build Solution
6. If necessary, change the startup project of the generated solution to the Pong_Game project.
Happy executing!

# Loops, Functions, I/O
## CRITERIA
* The project demonstrates an understanding of C++ functions and control structures.
  * This is easily determined by viewing the code.
  * You may review the header files to see code organized into functions.
* The project reads data from a file and process the data, or the program writes data to a file.
  * src/fileOps.cpp #17,40
* The project accepts user input and processes the input.
  * src/controller.cpp #34
  * src/game.cpp #68

# Object Oriented Programming
## CRITERIA
* The project uses Object Oriented Programming techniques.
  * Please review the code overall for h interfaces and cpp impls.
* Classes use appropriate access specifiers for class members.
  * You may review each header for these specific details.
* Class constructors utilize member initialization lists.
  * src/ball.cpp #10
  * src/consoleLogger.cpp #7
  * src/controller.cpp #10
  * src/fileOps.cpp #10 
  * src/game.cpp #9
  * src/gameObject.cpp #8 
  * src/messageQueue.cpp #8
  * src/paddle.cpp #7
  * src/renderer.cpp #8
* Classes abstract implementation details from their interfaces.
  * src/ball.cpp 
  * src/consoleLogger.cpp 
  * src/controller.cpp 
  * src/fileOps.cpp 
  * src/game.cpp 
  * src/gameObject.cpp  
  * src/messageQueue.cpp 
  * src/paddle.cpp
  * src/renderer.cpp
* Classes encapsulate behavior.
  * See class list above.
* Classes follow an appropriate inheritance hierarchy.
  * src/ball.h
  * src/paddle.h  
* Overloaded functions allow the same function to operate on different parameters.
  * src/ball.h #47
* Derived class functions override virtual base class functions.
  * src/ball.h #49
  * src/paddle.h #19
* Templates generalize functions in the project.
  * src/messsageQueue.h #12

# Memory Management
## CRITERIA
* The project makes use of references in function declarations.
  * src/ball.cpp #9 #53
  * src/controller.cpp #8
  * src/game.cpp #7 #89
  * src/paddle.cpp #17
  * src/renderer.cpp #7
* The project uses destructors appropriately.
  * src/renderer.cpp #83
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
  * Effective use of the stack in main.cpp and consoleLogger.cpp ensure that all items are deleted when scope is exited. Using unique_lock and lock_guard in messageQueue.cpp #15,27 ensure that these items are cleaned up in case of any exception.
* The project follows the Rule of 5.
  * n/a, all created classes are passed via smart pointer reference or reference. Objects that are moved are part of the standard library.
* The project uses move semantics to move data, instead of copying it, where possible.
  * Moving the copied string into the stack in src/consoleLogger.cpp
* The project uses smart pointers instead of raw pointers.
  * There are no pointer references in the code, smart pointers are created and passed by reference. src/main.cpp #22,23,24

# Concurrency
## CRITERIA
* The project uses multithreading.
  * src/main.cpp #18, 28, 32
* A promise and future is used in the project.
  * src/main.cpp 28, 32
* A mutex or lock is used in the project.
  * src/messageQueue.cpp # 14, 27
* A condition variable is used in the project.
  * src/messageQueue.cpp #15, #31