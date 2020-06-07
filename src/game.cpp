//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "game.h"
#include <cmath>

Game::Game(const size_t screenWidth, const size_t screenHeight, const Uint32 msPerFrame)
    : _screenHeight{screenHeight}, _screenWidth{screenWidth}, _msPerFrame{msPerFrame},
      _leftPaddle(0, screenHeight / 2),
      _rightPaddle(screenWidth, screenHeight / 2),
      _ball(screenWidth / 2, screenHeight / 2, -200.0f, 235.0f) {
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
        UpdateGame(deltaTime);
        GenerateOutput();
    }
}

void Game::ProcessInput(const float &deltaTime) {
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
    _leftPaddle.setDirection(0);
    if (state[SDL_SCANCODE_W]) {
        _leftPaddle.setDirection(-1);
    }
    if (state[SDL_SCANCODE_S]) {
        _leftPaddle.setDirection(1);
    }

    _rightPaddle.setDirection(0);
    if (state[SDL_SCANCODE_UP]) {
        _rightPaddle.setDirection(-1);
    }
    if (state[SDL_SCANCODE_DOWN]) {
        _rightPaddle.setDirection(1);
    }
}

void Game::UpdateGame(const float &deltaTime) {

    // Now execute direction
    if (_leftPaddle.getDirection() != 0) {
        float newY = _leftPaddle.getY() + (_leftPaddle.getDirection() * 300.0f * deltaTime);
        _leftPaddle.setY(newY);
        // Make sure the paddle doesn't move off screen.
        if (_leftPaddle.getY() < (Paddle::height / 2.0f + GameObject::thickness)) {
            _leftPaddle.setY(Paddle::height / 2.0f + GameObject::thickness);
        } else if (_leftPaddle.getY() > (_screenHeight - Paddle::height / 2.0f - GameObject::thickness)) {
            _leftPaddle.setY(_screenHeight - Paddle::height / 2.0f - GameObject::thickness);
        }
    }

    // Now execute direction
    if (_rightPaddle.getDirection() != 0) {
        float newY = _rightPaddle.getY() + (_rightPaddle.getDirection() * 300.0f * deltaTime);
        _rightPaddle.setY(newY);
        // Make sure the paddle doesn't move off screen.
        if (_rightPaddle.getY() < (Paddle::height / 2.0f + GameObject::thickness)) {
            _rightPaddle.setY(Paddle::height / 2.0f + GameObject::thickness);
        } else if (_rightPaddle.getY() > (_screenHeight - Paddle::height / 2.0f - GameObject::thickness)) {
            _rightPaddle.setY(_screenHeight - Paddle::height / 2.0f - GameObject::thickness);
        }
    }

    // These if's could be combined but this is relatively cleaner.
    if (_ball.getY() <= GameObject::thickness && _ball.getVelY() < 0.0f) {
        _ball.setVelY(_ball.getVelY() * -1);
    } else if (_ball.getY() >= _screenHeight - GameObject::thickness && _ball.getVelY() > 0.0f) {
        _ball.setVelY(_ball.getVelY() * -1);
    }

    // Determine if paddle has hit the ball.
    const float leftPaddleBallDiff = std::abs(_ball.getY() - _leftPaddle.getY());
    const float rightPaddleBallDiff = std::abs(_ball.getY() - _rightPaddle.getY());
    //SDL_Log("ball parameters: leftPaddleBallDiff=%f,ballX=%f,ballY=%f", leftPaddleBallDiff, _ball.getX(), _ball.getY());

    if (// our y-difference is small enough
            leftPaddleBallDiff <= Paddle::height / 2.0f &&
            _ball.getX() <= (GameObject::thickness * 2) && _ball.getX() >= GameObject::thickness &&
            // ball is moving left
            _ball.getVelX() < 0.0f) {
        _ball.setVelX(_ball.getVelX() * -1.1f);
    }
    else if (// our y-difference is small enough
            rightPaddleBallDiff <= Paddle::height / 2.0f &&
            _ball.getX() <= _screenWidth - GameObject::thickness && _ball.getX() >= _screenWidth - (GameObject::thickness * 2) &&
            // ball is moving right
            _ball.getVelX() > 0.0f) {
        _ball.setVelX(_ball.getVelX() * -1.1f );
    }

    _ball.setX(_ball.getX() + _ball.getVelX() * deltaTime);
    _ball.setY(_ball.getY() + _ball.getVelY() * deltaTime);
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
