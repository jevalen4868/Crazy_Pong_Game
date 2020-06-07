//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "paddle.h"

Paddle::Paddle(float x, float y) : GameObject{x, y} {

}
int Paddle::getDirection() const {
    return direction;
}
void Paddle::setDirection(int direction) {
    Paddle::direction = direction;
}
