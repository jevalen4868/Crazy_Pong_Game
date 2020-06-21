#ifndef PONG_GAME_CONFIGURATION_H
#define PONG_GAME_CONFIGURATION_H

#include <string>
#include "SDL.h"

using std::string;

class Cfg {
public:
    static constexpr Uint32 framesPerSecond{144};
    static constexpr Uint32 msPerFrame{1000 / framesPerSecond};
    static constexpr size_t screenWidth{1024};
    static constexpr size_t screenHeight{768};
};

#endif//PONG_GAME_CONFIGURATION_H
