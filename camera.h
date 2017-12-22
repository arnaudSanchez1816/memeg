#ifndef CAMERA_H
#define CAMERA_H

#include <QVector2D>
#include <QOpenGLWidget>
#include <QMatrix4x4>
#include "gameobject.h"

typedef enum Camera_Movement {
    Z,
    S,
    Q,
    D,
    C,
    W
} Camera_Movement;

class Camera : public GameObject
{
public:
    Camera()
        :worldUp(QVector3D(0.0f, 1.0f, 0.0f))
    {}
    void processKeyPress(Camera_Movement movement);
    void processMouseMovement(float xoffset, float yoffset);
    void lookAt(QMatrix4x4 &matrix);
    void draw(Renderer &renderer) override;

    QVector3D getWorldUp();

private:
    QVector3D worldUp;
};

#endif // CAMERA_H
