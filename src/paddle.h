//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_PADDLE_H
#define PONG_GAME_PADDLE_H

#include "gameObject.h"

class Paddle : public GameObject {
public:
    Paddle(float x, float y);
    static constexpr int height{150};
private:
    int direction{0};

public:
    void setDirection(int direction);

public:
    int getDirection() const;
};


#endif//PONG_GAME_PADDLE_H
