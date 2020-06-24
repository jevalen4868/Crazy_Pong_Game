//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "renderer.h"

Renderer::Renderer(const shared_ptr<Paddle> &leftPaddle, const shared_ptr<Paddle> &rightPaddle, const shared_ptr<Ball> &ball)
	: _leftPaddle{leftPaddle},
      _rightPaddle{rightPaddle},
      _ball(ball) {
    int sdlResult{SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)};
    if (sdlResult != 0) {
        SDL_Log("Unable to init SDL: %s", SDL_GetError());
    }
    _gameWindow = SDL_CreateWindow("Crazy Pong",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   Cfg::screenWidth,
                                   Cfg::screenHeight,
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

void Renderer::Render() const {
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
                     static_cast<int>(Cfg::screenWidth),
                     GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &topWall);

    SDL_Rect bottomWall{0,
                        static_cast<int>(Cfg::screenHeight) - GameObject::thickness,
                        static_cast<int>(Cfg::screenWidth),
                        GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &bottomWall);

    SDL_Rect leftPaddle{static_cast<int>(_leftPaddle->GetX() + GameObject::thickness),
                        static_cast<int>(_leftPaddle->GetY() - Paddle::height / 2),
                        GameObject::thickness,
                        Paddle::height};
    SDL_RenderFillRect(_gameRenderer, &leftPaddle);

    SDL_Rect ball{static_cast<int>(_ball->GetX() - GameObject::thickness / 2),
                  static_cast<int>(_ball->GetY() - GameObject::thickness / 2),
                  GameObject::thickness,
                  GameObject::thickness};
    SDL_RenderFillRect(_gameRenderer, &ball);

    SDL_Rect rightPaddle{static_cast<int>(_rightPaddle->GetX() - GameObject::thickness * 2),
                         static_cast<int>(_rightPaddle->GetY() - Paddle::height / 2),
                         GameObject::thickness,
                         Paddle::height};
    SDL_RenderFillRect(_gameRenderer, &rightPaddle);

    SDL_RenderPresent(_gameRenderer);
}

void Renderer::UpdateWindowTitle(const string &title) {

    SDL_SetWindowTitle(_gameWindow, title.c_str());
}

Renderer::~Renderer() {
    SDL_DestroyRenderer(_gameRenderer);
    SDL_DestroyWindow(_gameWindow);
    SDL_Quit();
}
