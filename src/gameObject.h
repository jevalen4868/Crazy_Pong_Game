//
// Created by jeremyvalenzuela on 6/6/20.
//

#ifndef PONG_GAME_GAMEOBJECT_H
#define PONG_GAME_GAMEOBJECT_H

class GameObject {
public:
    GameObject(float x, float y);
    static constexpr int thickness{15};
    float getX() { return _x; }
    float getY() { return _y; }
    void setX(float x) { _x = x; }
    void setY(float y) { _y = y; }
private:
    float _x, _y;
};


#endif//PONG_GAME_GAMEOBJECT_H
