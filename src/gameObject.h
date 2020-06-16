//
// Created by jeremyvalenzuela on 6/6/20.
//

#ifndef PONG_GAME_GAMEOBJECT_H
#define PONG_GAME_GAMEOBJECT_H

#include "cfg.h"

class GameObject {
private:
    float _x{0.0f}, _y{0.0f};

public:
    GameObject(float x, float y);
    static constexpr int thickness{15};
    void setX(float x);
    void setY(float y);
    float GetX() const;
    float GetY() const;
    virtual void Move(const float &deltaTime) = 0;
};


#endif//PONG_GAME_GAMEOBJECT_H
