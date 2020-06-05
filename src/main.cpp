#include <iostream>
#include "game.h"

int main() {
    std::cout << "Initializing crazy nasty arse Pong game." << std::endl;
    Game game;
    game.RunLoop();
    return 0;
}
