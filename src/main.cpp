#include <iostream>
#include "game.h"

int main() {

    constexpr Uint32 framesPerSecond{60};
    constexpr Uint32 msPerFrame{1000 / framesPerSecond};
    constexpr size_t screenWidth{1024};
    constexpr size_t screenHeight{768};

    std::cout << "Initializing crazy nasty arse Pong game." << std::endl;
    Game game{screenWidth, screenHeight, msPerFrame};
    game.RunLoop();

    return 0;
}
