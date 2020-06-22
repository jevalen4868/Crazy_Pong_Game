//
// Created by jeremyvalenzuela on 6/4/20.
//

#include "paddle.h"

Paddle::Paddle(float x, float y) : GameObject{x, y} {

}
int Paddle::GetDirection() const {
    return direction;
}
void Paddle::SetDirection(int direction) {
    Paddle::direction = direction;
}

void Paddle::Move(const float &deltaTime) {
    // Now execute direction
    if (GetDirection() != 0) {
        float newY = GetY() + (GetDirection() * 300.0f * deltaTime);
        SetY(newY);
        // Make sure the paddle doesn't move off screen.
        if (GetY() < (Paddle::height / 2.0f + GameObject::thickness)) {
            SetY(Paddle::height / 2.0f + GameObject::thickness);
        } else if (GetY() > (Cfg::screenHeight - Paddle::height / 2.0f - GameObject::thickness)) {
            SetY(Cfg::screenHeight - Paddle::height / 2.0f - GameObject::thickness);
        }
    }
}