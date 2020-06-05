//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "game.h"

Game::Game() {
    int sdlResult {SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)};
    if(sdlResult != 0) {
        SDL_Log("Unable to init SDL: %s", SDL_GetError());
    }
    _gameWindow = SDL_CreateWindow("Crazy Pong",
                               100,
                               100,
                               1024,
                               768,
                               SDL_WINDOW_OPENGL);
    if(!_gameWindow) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }
}

void Game::RunLoop() {
    while(_running) {
        SDL_Delay(1);
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

Game::~Game() {
    SDL_DestroyWindow(_gameWindow);
    SDL_Quit();
}

void Game::ProcessInput() {
}

void Game::UpdateGame() {
}

void Game::GenerateOutput() {
}

