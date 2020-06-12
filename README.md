# Welcome to Pong_Game

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