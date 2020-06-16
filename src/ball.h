//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_BALL_H
#define PONG_GAME_BALL_H

#include <random>
#include "paddle.h"
#include "gameObject.h"

using std::shared_ptr; 

class Ball : public GameObject {
private:
    float _velX{200.0f}, _velY{200.0f};

    shared_ptr<Paddle> _leftPaddle;
    shared_ptr<Paddle> _rightPaddle;

    // random number generator
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> _randomVel;
    std::uniform_int_distribution<int> _randomVelIncrease;
    std::uniform_int_distribution<int> _coinFlip;

public:
    Ball(float x, float y, shared_ptr<Paddle> &leftPaddle, shared_ptr<Paddle> &rightPaddle);
    void SetVelX(float velX);
    void SetVelY(float velY);
    void ResetBall();
    float GetVelX() const;
    float GetVelY() const;
    void Move(const float &deltaTime);
};


#endif//PONG_GAME_BALL_H
