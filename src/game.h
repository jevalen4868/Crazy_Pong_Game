//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_GAME_H
#define PONG_GAME_GAME_H

#include <random>
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
    void InitializeBall();
    void ProcessInput(const float &deltaTime);
    void UpdateGame(const float &deltaTime);
    void GenerateOutput();
    void UpdateWindowTitle(const int &fps);

    // Window created by SDL
    SDL_Window* _gameWindow;
    SDL_Renderer *_gameRenderer;

    Paddle _leftPaddle;
    Paddle _rightPaddle;
    int _leftScore {0};
    int _rightScore {0};
    bool _playerScored{false};
    Ball _ball;

    // Game should continue to run
    bool _running {true};
    const Uint32 _msPerFrame;
    const size_t _screenHeight;
    const size_t _screenWidth;

    // random number generator
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> _randomVel;
    std::uniform_int_distribution<int> _randomVelIncrease;
    std::uniform_int_distribution<int> _coinFlip;
};


#endif//PONG_GAME_GAME_H
