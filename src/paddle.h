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
    void GetDirection(int direction);
    int GetDirection() const;
    void Move(const float &deltaTime);

private:
    int direction{0};
};


#endif//PONG_GAME_PADDLE_H
