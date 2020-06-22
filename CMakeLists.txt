cmake_minimum_required(VERSION 3.16)
project(Pong_Game)

set(CMAKE_CXX_STANDARD 17)
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

#followed https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/ for windows
if(CMAKE_HOST_WIN32) 
	set(SDL2_DIR "${CMAKE_SOURCE_DIR}/cmake/SDL2-2.0.12/" )
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(Pong_Game src/main.cpp src/controller.cpp src/controller.h src/game.cpp src/game.h src/renderer.cpp src/renderer.h src/paddle.cpp src/paddle.h src/ball.cpp src/ball.h src/gameObject.cpp src/gameObject.h src/cfg.h src/fileOps.cpp src/fileOps.h src/messageQueue.cpp src/messageQueue.h src/consoleLogger.cpp src/consoleLogger.h)
if(CMAKE_HOST_UNIX) 
	string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
endif()
target_link_libraries(Pong_Game ${SDL2_LIBRARIES})