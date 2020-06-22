//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_CONTROLLERS_H
#define PONG_GAME_CONTROLLERS_H

#include <thread>
#include "paddle.h"

using std::shared_ptr;

class Controller {
private:
    // shared ptr to the paddle this controller will update.
    shared_ptr<Paddle> _paddlePtr;
    // how often the controller should update.
    const Uint32 _msPerFrame{16};
    // is the controller running.
    bool _running{true};
    // which key moves the paddle up.
    const Uint8 _upKey{0};
    // which key moves the paddle down.
    const Uint8 _downKey{0};
    // the player name
    string _playerName;

public:
    Controller(shared_ptr<Paddle> &paddlePtr, const Uint32 msPerFrame, Uint8 upKey, Uint8 downKey, const string playerName);
    // should be run in thread as it polls user input.
    string Control();
    // reflects the state of the controller loop.
    void IsRunning(bool running);
};


#endif//PONG_GAME_CONTROLLERS_H
