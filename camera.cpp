#include "camera.h"
#include <QtMath>
#include <iostream>
#include "mainwidget.h"

void Camera::processKeyPress(Camera_Movement movement) {
    float cameraSpeed = 30.0f * MainWidget::deltaTime;
    QVector3D cameraPos = this->getPos();
    if(movement == Camera_Movement::Z) {
        cameraPos += cameraSpeed * getFront();
    }
    if(movement == Camera_Movement::S) {
        cameraPos -= cameraSpeed * getFront();
    }
    if(movement == Camera_Movement::Q) {
        cameraPos -= QVector3D::crossProduct(getFront(),getUp()).normalized() * cameraSpeed;
    }
    if(movement == Camera_Movement::D) {
        cameraPos += QVector3D::crossProduct(getFront(),getUp()).normalized() * cameraSpeed;
    }
    if(movement == Camera_Movement::C) {
        cameraPos += cameraSpeed * getUp();
    }
    if(movement == Camera_Movement::W) {
        cameraPos -= cameraSpeed * getUp();
    }
    translate(cameraPos.x(), cameraPos.y(), cameraPos.z());
}

void Camera::processMouseMovement(float xoffset, float yoffset) {
    float mouseSensitivity = 10.0f * MainWidget::deltaTime;
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    float yaw = _rotY - xoffset;
    float pitch = _rotX - yoffset;

    if(pitch > 89.0f) {
        pitch = 89.0f;
    }
    if(pitch < -89.0f) {
        pitch = -89.0f;
    }
    rotateY(yaw);
    rotateX(pitch);
}

void Camera::lookAt(QMatrix4x4 &matrix) {
    QVector3D target = getPos() + getFront();
    matrix.lookAt(getPos(), target, getUp());
}

QVector3D Camera::getWorldUp() {
    return worldUp;
}

void Camera::draw(Renderer &renderer) {
    drawChild(renderer);
}
