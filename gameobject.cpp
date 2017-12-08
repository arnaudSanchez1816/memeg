#include "gameobject.h"

void GameObject::setOrigin(float x, float y, float z) {
    _transform.translate(x, y, z);
}
void GameObject::setScale(float x, float y, float z) {
    _transform.scale(x, y, z);
}

void GameObject::rotateX(float val) {
    _transform.rotate(val, 1.0f, 0.0f, 0.0f);
}

void GameObject::rotateY(float val) {
    _transform.rotate(val, 0.0f, 1.0f, 0.0f);
}

void GameObject::rotateZ(float val) {
    _transform.rotate(val, 0.0f, 0.0f, 1.0f);
}
