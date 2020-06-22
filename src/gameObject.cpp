//
// Created by jeremyvalenzuela on 6/6/20.
//

#include "gameObject.h"

GameObject:: GameObject(float x, float y) :
_x{x}, _y{y} {

}
float GameObject::GetX() const {
    return _x;
}
float GameObject::GetY() const {
    return _y;
}
void GameObject::SetX(float x) {
    _x = x;
}
void GameObject::SetY(float y) {
    _y = y;
}
