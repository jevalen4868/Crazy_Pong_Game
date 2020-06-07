//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "ball.h"

Ball::Ball(float x, float y, float velX, float velY) : GameObject{x, y}, _velX{velX}, _velY{velY} {

}
float Ball::getVelX() const {
    return _velX;
}
float Ball::getVelY() const {
    return _velY;
}
void Ball::setVelX(float velX) {
    _velX = velX;
}
void Ball::setVelY(float velY) {
    _velY = velY;
}
