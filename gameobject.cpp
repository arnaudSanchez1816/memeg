#include "gameobject.h"

void GameObject::translate(float x, float y = 0.0, float z = 0.0) {
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

QVector3D GameObject::getPos() {
    QVector4D posM = _transform.column(3);

    return QVector3D(posM.x(), posM.y(), posM.z());
}
