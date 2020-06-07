//
// Created by jeremyvalenzuela on 6/6/20.
//

#ifndef PONG_GAME_GAMEOBJECT_H
#define PONG_GAME_GAMEOBJECT_H

class GameObject {
public:
    GameObject(float x, float y);
    static constexpr int thickness{15};

private:
    float _x, _y;

public:
    void setX(float x);
    void setY(float y);

public:
    float getX() const;
    float getY() const;
};


#endif//PONG_GAME_GAMEOBJECT_H
