//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "game.h"
#include <cmath>
#include <iostream>
#include <string>

Game::Game(const size_t screenWidth, const size_t screenHeight, const Uint32 msPerFrame,
           shared_ptr<Paddle> &leftPaddle, shared_ptr<Paddle> &rightPaddle)
    : _screenHeight{screenHeight}, _screenWidth{screenWidth}, _msPerFrame{msPerFrame},
      _leftPaddle{leftPaddle},
      _rightPaddle{rightPaddle},
      engine(dev()),
      _randomVel(200, 250),
      _randomVelIncrease(0, 100),
      _coinFlip(0, 1),
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
    InitializeBall();
}

void Game::InitializeBall() {
    // Configure placement of ball.
    int coinFlipX{_coinFlip(engine)}, coinFlipY{_coinFlip(engine)};
    int velX{_randomVel(engine)}, velY{_randomVel(engine)};
    // coin flip for pos or neg.
    _ball.setX(_screenWidth / 2);
    _ball.setY(_screenHeight / 2);
    if(coinFlipX == 0) { velX *= -1; }
    if(coinFlipY == 0) { velY *= -1; }
    _ball.setVelX(velX);
    _ball.setVelY(velY);
}

void Game::RunLoop() {
    Uint32 frameStart = SDL_GetTicks();
    Uint32 frameEnd = SDL_GetTicks();
    Uint32 refreshTitleTimestamp = SDL_GetTicks();
    int fps {0};
    while (_running) {

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), frameStart + _msPerFrame)) {
            SDL_Delay(1);
        };

        float deltaTime = (SDL_GetTicks() - frameStart) / 1000.0f;
        if (deltaTime > 0.05f) {
            deltaTime = 0.05f;
        }

        frameStart = SDL_GetTicks();

        ProcessInput(deltaTime);
        UpdateGame(deltaTime);

        // Refresh the title once a second.
        if(frameEnd - refreshTitleTimestamp >= 1000) {
            UpdateWindowTitle(fps);
            fps = 0;
            refreshTitleTimestamp = frameEnd;
        }

        GenerateOutput();
        fps++;

        frameEnd = SDL_GetTicks();
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
    if(state[SDL_SCANCODE_RETURN] && _playerScored) {
        // reset ball state.
        _playerScored = false;
        InitializeBall();
    }

    /* Determine direction.
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
    }*/
}

void Game::UpdateGame(const float &deltaTime) {

    // Now execute direction
    if (_leftPaddle->getDirection() != 0) {
        float newY = _leftPaddle->getY() + (_leftPaddle->getDirection() * 300.0f * deltaTime);
        _leftPaddle->setY(newY);
        // Make sure the paddle doesn't move off screen.
        if (_leftPaddle->getY() < (Paddle::height / 2.0f + GameObject::thickness)) {
            _leftPaddle->setY(Paddle::height / 2.0f + GameObject::thickness);
        } else if (_leftPaddle->getY() > (_screenHeight - Paddle::height / 2.0f - GameObject::thickness)) {
            _leftPaddle->setY(_screenHeight - Paddle::height / 2.0f - GameObject::thickness);
        }
    }

    // Now execute direction
    if (_rightPaddle->getDirection() != 0) {
        float newY = _rightPaddle->getY() + (_rightPaddle->getDirection() * 300.0f * deltaTime);
        _rightPaddle->setY(newY);
        // Make sure the paddle doesn't move off screen.
        if (_rightPaddle->getY() < (Paddle::height / 2.0f + GameObject::thickness)) {
            _rightPaddle->setY(Paddle::height / 2.0f + GameObject::thickness);
        } else if (_rightPaddle->getY() > (_screenHeight - Paddle::height / 2.0f - GameObject::thickness)) {
            _rightPaddle->setY(_screenHeight - Paddle::height / 2.0f - GameObject::thickness);
        }
    }

    // These if's could be combined but this is relatively cleaner.
    if (_ball.getY() <= GameObject::thickness && _ball.getVelY() < 0.0f) {
        _ball.setVelY(_ball.getVelY() * -1);
    } else if (_ball.getY() >= _screenHeight - GameObject::thickness && _ball.getVelY() > 0.0f) {
        _ball.setVelY(_ball.getVelY() * -1);
    }

    // Determine if paddle has hit the ball.
    const float leftPaddleBallDiff = std::abs(_ball.getY() - _leftPaddle->getY());
    const float rightPaddleBallDiff = std::abs(_ball.getY() - _rightPaddle->getY());
    //SDL_Log("ball parameters: leftPaddleBallDiff=%f,ballX=%f,ballY=%f", leftPaddleBallDiff, _ball.getX(), _ball.getY());

    if (// our y-difference is small enough
            leftPaddleBallDiff <= Paddle::height / 2.0f &&
            _ball.getX() <= (GameObject::thickness * 2) && _ball.getX() >= GameObject::thickness &&
            // ball is moving left
            _ball.getVelX() < 0.0f) {
        const float newVelXIncrease = -1.0f - (_randomVelIncrease(engine) / 1000.0f);
        //SDL_Log("ball newVelXIncrease=%f", newVelXIncrease);
        _ball.setVelX(_ball.getVelX() * newVelXIncrease);
    }
    else if (// our y-difference is small enough
            rightPaddleBallDiff <= Paddle::height / 2.0f &&
            _ball.getX() <= _screenWidth - GameObject::thickness && _ball.getX() >= _screenWidth - (GameObject::thickness * 2) &&
            // ball is moving right
            _ball.getVelX() > 0.0f) {
        const float newVelXIncrease = -1.0f - (_randomVelIncrease(engine) / 1000.0f);
        //SDL_Log("ball newVelXIncrease=%f", newVelXIncrease);
        _ball.setVelX(_ball.getVelX() * newVelXIncrease );
    }

    _ball.setX(_ball.getX() + _ball.getVelX() * deltaTime);
    _ball.setY(_ball.getY() + _ball.getVelY() * deltaTime);

    // Check if either side has scored
    if(_ball.getX() < 0 && !_playerScored) {
        _rightScore++;
        _playerScored = true;
    } else if (_ball.getX() > _screenWidth && !_playerScored) {
        _leftScore++;
        _playerScored = true;
    }
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

    SDL_Rect leftPaddle{static_cast<int>(_leftPaddle->getX() + GameObject::thickness),
                        static_cast<int>(_leftPaddle->getY() - Paddle::height / 2),
                        GameObject::thickness,
                        Paddle::height};
    SDL_RenderFillRect(_gameRenderer, &leftPaddle);

    SDL_Rect ball{static_cast<int>(_ball.getX() - GameObject::thickness / 2),
                  static_cast<int>(_ball.getY() - GameObject::thickness / 2),
                  GameObject::thickness,
                  GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &ball);

    SDL_Rect rightPaddle{static_cast<int>(_rightPaddle->getX() - GameObject::thickness * 2),
                         static_cast<int>(_rightPaddle->getY() - Paddle::height / 2),
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

void Game::UpdateWindowTitle(const int &fps) {
    std::string title;
    if(_playerScored) {
        title = "Game over! Hit enter to continue or ESC to quit. Player1: "
                + std::to_string(_leftScore)
                + " Player2: " + std::to_string(_rightScore);
    } else {
        title = "Crazy Pong FPS: " + std::to_string(fps)
                + " Player1: " + std::to_string(_leftScore)
                + " Player2: " + std::to_string(_rightScore);
    }
    SDL_SetWindowTitle(_gameWindow, title.c_str());
}

bool Game::IsRunning() {
    return _running;
}
