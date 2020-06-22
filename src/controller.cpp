//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "SDL.h"
#include "controller.h"

Controller::Controller(shared_ptr<Paddle> &paddlePtr, const Uint32 msPerFrame,
    Uint8 upKey, Uint8 downKey, const string playerName) 
    : _paddlePtr{paddlePtr}, _msPerFrame{msPerFrame}, _upKey{upKey}, _downKey{downKey}, _playerName{playerName} {
}

string Controller::Control() {
    Uint32 frameStart = SDL_GetTicks();
    Uint32 frameEnd = SDL_GetTicks();
    while (_running) {
       //SDL_Log("_paddlePtr Direction=%i", _paddlePtr->getDirection());

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), frameStart + _msPerFrame)) {
            SDL_Delay(1);
        };

        frameStart = SDL_GetTicks();

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    _running = false;
                    break;
            }
        }

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        // Determine direction.
        _paddlePtr->SetDirection(0);
        if (state[_upKey]) {
            _paddlePtr->SetDirection(-1);
        }
        if (state[_downKey]) {
            _paddlePtr->SetDirection(1);
        }

        frameEnd = SDL_GetTicks();

        //SDL_Log("_paddlePtr Direction=%i", _paddlePtr->getDirection());
    }
    return _playerName;
}

void Controller::IsRunning(bool running) {
    _running = running;
}
