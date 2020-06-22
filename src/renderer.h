//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_RENDERER_H
#define PONG_GAME_RENDERER_H

#include <thread>
#include <string>
#include "SDL.h"
#include "paddle.h"
#include "ball.h"
#include "cfg.h"

using std::thread;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;

class Renderer {
public:
    Renderer(const shared_ptr<Paddle> &leftPaddle, const shared_ptr<Paddle> &rightPaddle, const shared_ptr<Ball> &ball);
    ~Renderer();
    void Render() const;
    void UpdateWindowTitle(const string &title);

private:
    // Window created by SDL
    SDL_Window *_gameWindow;
    SDL_Renderer *_gameRenderer;

    const shared_ptr<Paddle> _leftPaddle;
    const shared_ptr<Paddle> _rightPaddle;    
    const shared_ptr<Ball> _ball;    
};


#endif//PONG_GAME_RENDERER_H
