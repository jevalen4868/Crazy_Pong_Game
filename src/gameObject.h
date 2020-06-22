//
// Created by jeremyvalenzuela on 6/6/20.
//

#ifndef PONG_GAME_GAMEOBJECT_H
#define PONG_GAME_GAMEOBJECT_H

#include "cfg.h"

// Any class that has coordinates and movement can implement this interface.
class GameObject {
private:
    float _x{0.0f}, _y{0.0f};

public:
    GameObject(float x, float y);
    // default "thickness of objects in this game.
    static constexpr int thickness{15};
    // set the x coordinate of the obj.
    void SetX(float x);
    // set the y coordinate of the obj.
    void SetY(float y);
    // get the x coordinate of the obj.
    float GetX() const;
    // set the y coordinate of the obj.
    float GetY() const;
    // implement the movement of the object which typically updates x and y. 
    virtual void Move(const float &deltaTime) = 0;
};


#endif//PONG_GAME_GAMEOBJECT_H
