#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>

class GameObject
{
public:
    QMatrix4x4 _transform;

    GameObject()
        : _transform() {}

    void translate(float x, float y, float z);
    void setScale(float x, float y, float z);
    void rotateX(float val);
    void rotateY(float val);
    void rotateZ(float val);

    QVector3D getPos();
};

#endif // GAMEOBJECT_H
