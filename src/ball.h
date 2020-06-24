//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_BALL_H
#define PONG_GAME_BALL_H

#include <random>
#include <future>
#include "paddle.h"
#include "gameObject.h"

using std::shared_ptr; 

class Ball : public GameObject {
private:
    // velocity of ball in x and y direction.
    float _velX{200.0f}, _velY{200.0f};

    // reference to paddles the ball will bounce off of.
    shared_ptr<Paddle> _leftPaddle;
    shared_ptr<Paddle> _rightPaddle;

    // used for maintaining pause. returns state when done.
    bool _paused{false};

    // random number generator classes
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> _randomVel;
    std::uniform_int_distribution<int> _randomVelIncrease;
    std::uniform_int_distribution<int> _coinFlip;

public:
    Ball(float x, float y, shared_ptr<Paddle> &leftPaddle, shared_ptr<Paddle> &rightPaddle);
    // set velocity of ball in x
    void SetVelX(float velX);
    // set velocity of ball in y
    void SetVelY(float velY);
    // reset the ball to the center of the window.
    void ResetBall();
    // retrieve the x velocity of the ball.
    float GetVelX() const;
    // retrieve the x velocity of the ball.
    float GetVelY() const;
    // used to pause the ball movement
    void TogglePause();
    void TogglePause(const bool newValue);
    void Move(const float &deltaTime) override;
};


#endif//PONG_GAME_BALL_H
