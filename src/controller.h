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
    shared_ptr<Paddle> _paddlePtr;
    const Uint32 _msPerFrame{16};
    bool _running{true};
    const Uint8 _upKey{0};
    const Uint8 _downKey{0};

public:
    Controller(shared_ptr<Paddle> &paddlePtr, const Uint32 msPerFrame, Uint8 upKey, Uint8 downKey);
    void Control();
    void IsRunning(bool running);
};


#endif//PONG_GAME_CONTROLLERS_H
