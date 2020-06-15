//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_RENDERER_H
#define PONG_GAME_RENDERER_H

#include "SDL.h"
#include "paddle.h"
#include "ball.h""

class Renderer {
public:
    Renderer(const size_t screenWidth, const size_t screenHeight, const Uint32 msPerFrame);
    ~Renderer();
    void Render();

private:
    // Window created by SDL
    SDL_Window *_gameWindow;
    SDL_Renderer *_gameRenderer;

    Paddle _leftPaddle;
    Paddle _rightPaddle;    
    Ball _ball;

    const Uint32 _msPerFrame;
    const size_t _screenHeight;
    const size_t _screenWidth;
};


#endif//PONG_GAME_RENDERER_H
