//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_GAME_H
#define PONG_GAME_GAME_H

#include "SDL.h"
#include "paddle.h"
#include "ball.h"

class Game {
public:
    Game(const size_t screenWidth, const size_t screenHeight, const Uint32 msPerFrame);
    ~Game();
    // Runs the game loop until the game is over
    void RunLoop();
private:
    // Helper functions for the game loop
    void ProcessInput(const float deltaTime);
    void UpdateGame();
    void GenerateOutput();

    // Window created by SDL
    SDL_Window* _gameWindow;
    SDL_Renderer *_gameRenderer;

    Paddle _leftPaddle;
    Paddle _rightPaddle;
    Ball _ball;

    // Game should continue to run
    bool _running {true};
    const Uint32 _msPerFrame;
    const size_t _screenHeight;
    const size_t _screenWidth;

};


#endif//PONG_GAME_GAME_H
