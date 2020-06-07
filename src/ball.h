//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_BALL_H
#define PONG_GAME_BALL_H

#include "gameObject.h"

class Ball : public GameObject {

public:
    Ball(float x, float y, float velX, float velY);

private:
    float _velX, _velY;

public:
    void setVelX(float velX);
    void setVelY(float velY);

public:
    float getVelX() const;
    float getVelY() const;
};


#endif//PONG_GAME_BALL_H
