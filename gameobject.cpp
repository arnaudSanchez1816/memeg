#include "gameobject.h"
#include <QQuaternion>

void GameObject::translate(float x, float y, float z) {
    _x = x;
    _y = y;
    _z = z;
    updateAllTransform();
}
void GameObject::setScale(float x, float y, float z) {
    _sX = x;
    _sY = y;
    _sZ = z;
    updateAllTransform();
}

void GameObject::rotateX(float val) {
    _rotX = val;
    updateAllTransform();
}

void GameObject::rotateY(float val) {
    _rotY = val;
    updateAllTransform();
}

void GameObject::rotateZ(float val) {
    _rotZ = val;
    updateAllTransform();
}

QVector3D GameObject::getPos(bool relative) {
    if(!relative) {
        QVector4D absPos = _transform.column(3);
        return QVector3D(absPos.x(), absPos.y(), absPos.z());
    }
    return QVector3D(_x, _y, _z);
}

QVector3D GameObject::getFront() {
    QVector4D front = _transform.column(2);
    return QVector3D(front);
}

QVector3D GameObject::getUp() {
    QVector4D up = _transform.column(1);
    return QVector3D(up);
}

QVector3D GameObject::getRight() {
    QVector4D right = _transform.column(0);
    return QVector3D(right);
}

QMatrix4x4 GameObject::updateLocalTransform() {
    QMatrix4x4 transform;
    transform.translate(_x, _y, _z);
    transform.scale(_sX, _sY, _sX);
    transform.rotate(QQuaternion::fromEulerAngles(_rotX, _rotY, _rotZ));

    return transform;
}

void GameObject::updateAllTransform() {
    if(_parent.lock()) {
        _transform = _parent.lock()->_transform * updateLocalTransform();
    } else {
        _transform = updateLocalTransform();
    }
    for(auto &child : _children) {
        child->updateAllTransform();
    }
}

void GameObject::addChild(std::shared_ptr<GameObject> child) {
    child->setParent(shared_from_this());
    _children.emplace_back(child);
    updateAllTransform();
}


void GameObject::setParent(std::shared_ptr<GameObject> parent) {
    /*if(_parent.lock()) {
        _parent.lock()->removeChild(shared_from_this());
    }*/
    _parent = parent;
}

void GameObject::removeChild(std::shared_ptr<GameObject> child) {
    _children.remove(child);
    child->setParent(nullptr);
    updateAllTransform();
}

std::shared_ptr<GameObject> GameObject::getPtr() {
    return shared_from_this();
}

void GameObject::draw(Renderer &renderer) {
}

void GameObject::drawChild(Renderer &renderer) {
    for(auto &child : _children) {
        child->draw(renderer);
    }
}

std::list<std::shared_ptr<GameObject>>& GameObject::getChildren() {
    return _children;
}
