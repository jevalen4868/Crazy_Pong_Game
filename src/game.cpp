//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "game.h"

Game::Game(const size_t screenWidth, const size_t screenHeight, const size_t msPerFrame) {
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
    while (_running) {
        SDL_Delay(1);
        ProcessInput();
        UpdateGame();
        GenerateOutput();
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
}

void Game::UpdateGame() {
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(_gameRenderer,
                               0x00,
                               0x00,
                               0xFF,
                               0xFF);
    SDL_RenderClear(_gameRenderer);

    SDL_RenderPresent(_gameRenderer);
}

Game::~Game() {
    SDL_DestroyRenderer(_gameRenderer);
    SDL_DestroyWindow(_gameWindow);
    SDL_Quit();
}
