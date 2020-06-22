//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_GAME_H
#define PONG_GAME_GAME_H

#include <random>
#include <thread>
#include <cmath>
#include <iostream>
#include <string>
#include <filesystem>
#include "SDL.h"
#undef main
#include "paddle.h"
#include "ball.h"
#include "renderer.h"
#include "cfg.h"
#include "fileOps.h"

using std::shared_ptr;
using std::unique_ptr;

class Game {
public:
    Game(shared_ptr<Paddle> &leftPaddle, shared_ptr<Paddle> &rightPaddle, shared_ptr<Ball> &ball,
        Renderer &renderer);
    ~Game();
    // Runs the game loop until the game is over
    void RunLoop();
    // maintains the state of the game loop.
    bool IsRunning();
private:
    // Helper functions for the game loop for handling global user input for controlling the game state. 
    void ProcessInput();
    // Call all movement functions and execute other necessary game logic.
    void UpdateGame(const float &deltaTime);
    // Call the renderer and other necessary output.
    void GenerateOutput();

    // renderer object to be called in generate output.
    Renderer _renderer;

    // reference to paddles and ball for determining a score.
    shared_ptr<Paddle> _leftPaddle;
    shared_ptr<Paddle> _rightPaddle;
    shared_ptr<Ball> _ball;
    // various score state of the game.
    int _leftScore {0};
    int _previousLeftScore{0};
    int _rightScore {0};
    int _previousRightScore{0};
    // maintaining whether a player scored or not.
    bool _playerScored{false};

    // Game should continue to run
    bool _running {true};
};


#endif//PONG_GAME_GAME_H
