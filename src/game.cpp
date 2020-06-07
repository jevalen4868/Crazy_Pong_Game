//
// Created by jeremyvalenzuela on 6/4/20.
//

#include <iostream>
#include "game.h"

Game::Game(const size_t screenWidth, const size_t screenHeight, const Uint32 msPerFrame)
    : _screenHeight{screenHeight}, _screenWidth{screenWidth}, _msPerFrame{msPerFrame},
      _leftPaddle(0, screenHeight / 2),
      _rightPaddle(screenWidth, screenHeight / 2),
      _ball(screenWidth / 2, screenHeight / 2) {
    int sdlResult{SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)};
    if (sdlResult != 0) {
        SDL_Log("Unable to init SDL: %s", SDL_GetError());
    }
    _gameWindow = SDL_CreateWindow("Crazy Pong",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   screenWidth,
                                   screenHeight,
                                   SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (!_gameWindow) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }

    _gameRenderer = SDL_CreateRenderer(_gameWindow,
                                       -1,
                                       SDL_RENDERER_ACCELERATED);
    if (!_gameRenderer) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
    }
}

void Game::RunLoop() {
    Uint32 frameStart = SDL_GetTicks();
    while (_running) {

        // ~60 fps
        while (!SDL_TICKS_PASSED(SDL_GetTicks(), frameStart + this->_msPerFrame)) {
            SDL_Delay(1);
        };

        float deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }

        frameStart = SDL_GetTicks();

        ProcessInput(deltaTime);
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput(const float deltaTime) {
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

    // Determine direction.
    int leftPaddleDir{0};
    if (state[SDL_SCANCODE_W]) {
        leftPaddleDir -= 1;
    }
    if (state[SDL_SCANCODE_S]) {
        leftPaddleDir += 1;
    }
    // Now execute direction
    if (leftPaddleDir != 0) {
        float newY = _leftPaddle.getY() + (leftPaddleDir * 300.0f * deltaTime);
        _leftPaddle.setY(newY);
        // Make sure the paddle doesn't move off screen.
        if(_leftPaddle.getY() < (Paddle::height / 2.0f + GameObject::thickness)) {
            _leftPaddle.setY(Paddle::height / 2.0f + GameObject::thickness);
        }
        else if(_leftPaddle.getY() > (_screenHeight - Paddle::height / 2.0f - GameObject::thickness)) {
            _leftPaddle.setY(_screenHeight - Paddle::height / 2.0f - GameObject::thickness);
        }
    }
}

void Game::UpdateGame() {
}

void Game::GenerateOutput() {
    // draw background
    SDL_SetRenderDrawColor(_gameRenderer,
                           0x00,
                           0x00,
                           0xFF,
                           0xFF);

    SDL_RenderClear(_gameRenderer);

    SDL_SetRenderDrawColor(_gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    SDL_Rect topWall{0,
                     0,
                     static_cast<int>(_screenWidth),
                     GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &topWall);

    SDL_Rect bottomWall{0,
                        static_cast<int>(_screenHeight) - GameObject::thickness,
                        static_cast<int>(_screenWidth),
                        GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &bottomWall);

    SDL_Rect leftPaddle{static_cast<int>(_leftPaddle.getX() + GameObject::thickness),
                        static_cast<int>(_leftPaddle.getY() - Paddle::height / 2),
                        GameObject::thickness,
                        Paddle::height};
    SDL_RenderFillRect(_gameRenderer, &leftPaddle);

    SDL_Rect ball{static_cast<int>(_ball.getX() - GameObject::thickness / 2),
                  static_cast<int>(_ball.getY() - GameObject::thickness / 2),
                  GameObject::thickness,
                  GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &ball);

    SDL_Rect rightPaddle{static_cast<int>(_rightPaddle.getX() - GameObject::thickness * 2),
                         static_cast<int>(_rightPaddle.getY() - Paddle::height / 2),
                         GameObject::thickness,
                         Paddle::height};
    SDL_RenderFillRect(_gameRenderer, &rightPaddle);

    SDL_RenderPresent(_gameRenderer);
}

Game::~Game() {
    SDL_DestroyRenderer(_gameRenderer);
    SDL_DestroyWindow(_gameWindow);
    SDL_Quit();
}
