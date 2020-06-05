//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_GAME_H
#define PONG_GAME_GAME_H

#include "SDL.h"

class Game {
public:
    Game();
    ~Game();
    // Runs the game loop until the game is over
    void RunLoop();
private:
    // Helper functions for the game loop
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    // Window created by SDL
    SDL_Window* _gameWindow;
    // Game should continue to run
    bool _running;
};


#endif//PONG_GAME_GAME_H
