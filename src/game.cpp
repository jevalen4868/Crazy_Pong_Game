//
// Created by jeremyvalenzuela on 6/4/20.
//

#include <cmath>
#include <iostream>
#include <string>
#include <thread>
#include "game.h"

using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;

Game::Game(shared_ptr<Paddle> &leftPaddle, shared_ptr<Paddle> &rightPaddle, shared_ptr<Ball> &ball,
    Renderer &renderer)
    : _leftPaddle{leftPaddle},
      _rightPaddle{rightPaddle},
      _ball{ball},
      _renderer{renderer} {   
    _ball->ResetBall();
}

void Game::RunLoop() {
    Uint32 frameStart = SDL_GetTicks();
    Uint32 frameEnd = SDL_GetTicks();
    Uint32 refreshTitleTimestamp = SDL_GetTicks();
    int fps {0};
    while (_running) {

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), frameStart + Cfg::msPerFrame)) {
            SDL_Delay(1);
        };

        float deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }

        frameStart = SDL_GetTicks();

        ProcessInput();
        UpdateGame(deltaTime);

        // Refresh the title once a second.
        if(frameEnd - refreshTitleTimestamp >= 1000) {
            _renderer.UpdateWindowTitle(fps, _playerScored, _leftScore, _rightScore);
            fps = 0;
            refreshTitleTimestamp = frameEnd;
        }

        GenerateOutput();
        fps++;

        frameEnd = SDL_GetTicks();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _running = false;
                break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        _running = false;
    }
    if(state[SDL_SCANCODE_RETURN] && _playerScored) {
        // reset ball state.
        _playerScored = false;
        _ball->ResetBall();
    }
}

void Game::UpdateGame(const float &deltaTime) {
    _leftPaddle->Move(deltaTime);
    _rightPaddle->Move(deltaTime);
    _ball->Move(deltaTime);

    // Check if either side has scored
    if (_ball->GetX() < 0 && !_playerScored) {
        _rightScore++;
        _playerScored = true;
    } else if (_ball->GetX() > Cfg::screenWidth && !_playerScored) {
        _leftScore++;
        _playerScored = true;
    }
}

void Game::GenerateOutput() {
    _renderer.Render();
}

Game::~Game() {
}

bool Game::IsRunning() {
    return _running;
}
