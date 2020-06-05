//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_GAME_H
#define PONG_GAME_GAME_H

#include "SDL.h"

class Game {
public:
    Game(const size_t screenWidth, const size_t screenHeight, const size_t msPerFrame);
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
    SDL_Renderer *_gameRenderer;
    // Game should continue to run
    bool _running {true};
};


#endif//PONG_GAME_GAME_H
