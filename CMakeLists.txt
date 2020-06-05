cmake_minimum_required(VERSION 3.16)
project(Pong_Game)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Pong_Game src/main.cpp src/controllers.cpp src/controllers.h src/game.cpp src/game.h src/renderer.cpp src/renderer.h src/paddle.cpp src/paddle.h src/ball.cpp src/ball.h)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Pong_Game ${SDL2_LIBRARIES})