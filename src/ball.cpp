//
// Created by jeremyvalenzuela on 6/4/20.
//

#include <cmath>
#include <thread>
#include "ball.h"

Ball::Ball(float x, float y, shared_ptr<Paddle> &leftPaddle, shared_ptr<Paddle> &rightPaddle) 
    : GameObject{x, y}, 
    _leftPaddle{leftPaddle},
    _rightPaddle{rightPaddle},
    engine{dev()},
    _randomVel{200, 250},
    _randomVelIncrease{0, 100},
    _coinFlip{0, 1} {

}
float Ball::GetVelX() const {
    return _velX;
}
float Ball::GetVelY() const {
    return _velY;
}
void Ball::SetVelX(float velX) {
    _velX = velX;
}
void Ball::SetVelY(float velY) {
    _velY = velY;
}

void Ball::ResetBall() {
    // Configure placement of ball.
    int coinFlipX{_coinFlip(engine)}, coinFlipY{_coinFlip(engine)};
    int velX{_randomVel(engine)}, velY{_randomVel(engine)};
    // coin flip for pos or neg.
    SetX(Cfg::screenWidth / 2);
    SetY(Cfg::screenHeight / 2);
    if (coinFlipX == 0) { velX *= -1; }
    if (coinFlipY == 0) { velY *= -1; }
    SetVelX(velX);
    SetVelY(velY);
}

void Ball::TogglePause() {
    _paused = !_paused;
}

void Ball::Move(const float &deltaTime) {
    while (_paused) {
        return;
    }
    // These if's could be combined but this is relatively cleaner.
    if (GetY() <= GameObject::thickness && GetVelY() < 0.0f) {
        SetVelY(GetVelY() * -1);
    } else if (GetY() >= Cfg::screenHeight - GameObject::thickness && GetVelY() > 0.0f) {
        SetVelY(GetVelY() * -1);
    }

    // Determine if paddle has hit the ball.
    const float leftPaddleBallDiff = std::abs(GetY() - _leftPaddle->GetY());
    const float rightPaddleBallDiff = std::abs(GetY() - _rightPaddle->GetY());
    //SDL_Log("ball parameters: leftPaddleBallDiff=%f,ballX=%f,ballY=%f", leftPaddleBallDiff, _ball.getX(), _ball.getY());

    if (// our y-difference is small enough
            leftPaddleBallDiff <= Paddle::height / 2.0f &&
            GetX() <= (GameObject::thickness * 2) && GetX() >= GameObject::thickness &&
            // ball is moving left
            GetVelX() < 0.0f) {
        const float newVelXIncrease = -1.0f - (_randomVelIncrease(engine) / 1000.0f);
        //SDL_Log("ball newVelXIncrease=%f", newVelXIncrease);
        SetVelX(GetVelX() * newVelXIncrease);
    } else if (// our y-difference is small enough
            rightPaddleBallDiff <= Paddle::height / 2.0f &&
            GetX() <= Cfg::screenWidth - GameObject::thickness && GetX() >= Cfg::screenWidth - (GameObject::thickness * 2) &&
            // ball is moving right
            GetVelX() > 0.0f) {
        const float newVelXIncrease = -1.0f - (_randomVelIncrease(engine) / 1000.0f);
        //SDL_Log("ball newVelXIncrease=%f", newVelXIncrease);
        SetVelX(GetVelX() * newVelXIncrease);
    }

    SetX(GetX() + GetVelX() * deltaTime);
    SetY(GetY() + GetVelY() * deltaTime);
}
