#ifndef PONG_GAME_CONFIGURATION_H
#define PONG_GAME_CONFIGURATION_H

#include <string>
#include "SDL.h"

using std::string;

// contains game configuration constant values.
class Cfg {
public:
    // how often the app should run the controller update loop.
    static constexpr Uint32 sixtyMsPerUpdate{1000 / 60};
    // how often the game logic should execute and call the renderer.
    static constexpr Uint32 msPerFrame{1000 / 144};
    // screen width of app window.
    static constexpr size_t screenWidth{1024};
    // screen height of app window.
    static constexpr size_t screenHeight{768};
};

#endif//PONG_GAME_CONFIGURATION_H
