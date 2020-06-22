//
// Created by jeremyvalenzuela on 6/4/20.
//

#ifndef PONG_GAME_PADDLE_H
#define PONG_GAME_PADDLE_H

#include "gameObject.h"

class Paddle : public GameObject {
public:
    Paddle(float x, float y);
    // Default height of paddles
    static constexpr int height{150};
    // Set the direction of the paddle.
    void SetDirection(int direction);
    // Get the direction of the paddle.
    int GetDirection() const;
    void Move(const float &deltaTime) override;

private:
    int direction{0};
};


#endif//PONG_GAME_PADDLE_H
