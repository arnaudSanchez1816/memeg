/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwidget.h"

#include <QMouseEvent>
#include <math.h>
#include <iostream>
#include <QtMultimedia/QSound>
#include "utils.h"
#include <random>


float MainWidget::deltaTime = 0.0;
float MainWidget::lastFrame = 0.0;

float distancePlane = 2.0;

MainWidget::MainWidget(int fps, QWidget *parent) :
    QOpenGLWidget(parent),
    orbit(false),
    fps(fps),
    keys(5, false),
    gc(),
    torrusTime(0.0f)
{
    setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
   /* makeCurrent();
    doneCurrent();*/
}

void MainWidget::mousePressEvent(QMouseEvent *e) {
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e) {
    if(e->button() == Qt::RightButton) {
        orbit = !orbit;
    }
}

void MainWidget::wheelEvent(QWheelEvent *event) {
    int numDegrees = event->delta() / 8;
    float numSteps = numDegrees / 100.0;
    if (event->delta() > 0.0) {
        if(distancePlane > 1.0)
            distancePlane -= numSteps;
    } else {
        if(distancePlane < 4.0)
            distancePlane -= numSteps;
    }
    event->accept();
}

void MainWidget::timerEvent(QTimerEvent *) {
    update();
    //move
    float sensi = 20.0 * deltaTime;
    auto pos = jet->getPos();
    if(keys[0]) {
        pos.setY(pos.y() + sensi);
    }
    if(keys[1]) {
        pos.setX(pos.x() + sensi);
    }
    if(keys[2]) {
        pos.setY(pos.y() - sensi);
    }
    if(keys[3]) {
        pos.setX(pos.x() - sensi);
    }
    if(keys[4]) {
        particleEngineBullet->generateParticles(jet->getPos(), 80.0);
    }
    jet->translate(pos.x(), pos.y(), pos.z());
    //banking
    float rotSpeed = 150.0 * deltaTime;
    if(gc.bankingLeft) {
        gc.jetRotAngle = std::max(gc.jetRotAngle - rotSpeed, -30.0f);
    }
    if(gc.bankingRight) {
        gc.jetRotAngle = std::min(gc.jetRotAngle + rotSpeed, 30.0f);
    }
    if(!gc.bankingLeft and !gc.bankingRight) {
        if(gc.jetRotAngle > 0) {
            gc.jetRotAngle = std::max(gc.jetRotAngle - rotSpeed, 0.0f);
        } else {
            gc.jetRotAngle = std::min(gc.jetRotAngle + rotSpeed, 0.0f);
        }
    }
    jet->rotateZ(gc.jetRotAngle);
    jet->getChildren().front()->rotateZ(-gc.jetRotAngle);
}

void MainWidget::keyPressEvent(QKeyEvent *event) {
    /*Camera *cam = static_cast<Camera*>(camera.get());
    switch(event->key()) {
        case Qt::Key_Z:
            cam->processKeyPress(Camera_Movement::Z);
            break;
        case Qt::Key_S:
            cam->processKeyPress(Camera_Movement::S);
            break;
        case Qt::Key_Q:
            cam->processKeyPress(Camera_Movement::Q);
            break;
        case Qt::Key_D:
            cam->processKeyPress(Camera_Movement::D);
            break;
        case Qt::Key_C:
            cam->processKeyPress(Camera_Movement::C);
            break;
        case Qt::Key_W:
            cam->processKeyPress(Camera_Movement::W);
            break;
    }*/

    switch(event->key()) {
        case Qt::Key_Z:
            keys[0] = true;
            break;
        case Qt::Key_Q:
            keys[1] = true;
            gc.bankingLeft = true;
            break;
        case Qt::Key_S:
            keys[2] = true;
            break;
        case Qt::Key_D:
            keys[3] = true;
            gc.bankingRight = true;
            break;
        case Qt::Key_Space:
            keys[4] = true;
            break;
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_Z:
            keys[0] = false;
            break;
        case Qt::Key_Q:
            keys[1] = false;
            gc.bankingLeft = false;
            break;
        case Qt::Key_S:
            keys[2] = false;
            break;
        case Qt::Key_D:
            keys[3] = false;
            gc.bankingRight = false;
            break;
        case Qt::Key_Space:
            keys[4] = false;;
            break;
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event) {
/*
    if(event->buttons() & Qt::LeftButton) {
        float xoffset = event->x() - mousePressPosition.x();
        float yoffset = mousePressPosition.y() - event->y(); // reversed since y-coordinates range from bottom to top
        mousePressPosition = QVector2D(event->localPos());
        Camera *cam = static_cast<Camera*>(camera.get());
        cam->processMouseMovement(xoffset, yoffset);
    }
*/
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);
    initShaders();
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    // Enable back face culling
    //glEnable(GL_CULL_FACE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    particleEngineBullet = new ParticleEngine(ParticleType::Bullet, particlesProgram);
    scene = std::make_shared<Scene>();
    skybox = std::make_shared<Skybox>(sbProgram);
    //model = std::make_shared<Model>("assets/nanosuit/nanosuit.obj", &modelProgram);
    jet = std::make_shared<Model>("assets/jet/jet.3ds", &modelProgram);
    //nano = std::make_shared<Model>("assets/nanosuit/nanosuit.obj", &modelProgram);
    terrain = std::make_shared<Terrain>(200, 400, program, particlesProgram);
    camera = std::make_shared<Camera>();
    Camera *cam = static_cast<Camera*>(camera.get());
    gc.activeCamera = *cam;
    Terrain* t = static_cast<Terrain*>(terrain.get());
    t->addChunk(0.0, 0.0, 0.0);
    t->addChunk(0.0, 0.0, t->getSize());
    t->addChunk(0.0, 0.0, t->getSize() * 2);
    //scene->addChild(model);
    scene->addChild(terrain);
    scene->addChild(skybox);
    //model->addChild(jet);
    //model->rotateY(180);
    //jet->addChild(nano);
    scene->addChild(jet);
    jet->addChild(camera);
    jet->translate(t->getSize() / 2.0, 15.0, 0.0);
    camera->translate(0.0, 0.5, -3.0);
    //nano->translate(0.0, 0.0, 20.0);
    // Use QBasicTimer because its faster than QTimer
    timer.start(1000/fps, this);
}

void MainWidget::generateTorus() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(50.0, 150.0);
    std::uniform_real_distribution<> disZ(80, 120.0);
    std::uniform_real_distribution<> disY(15.0, 18.0);
    std::uniform_real_distribution<> disSize(3.0, 5.0);
    std::shared_ptr<GameObject> torus = std::make_shared<Model>("assets/torus/chienne.3ds", &modelProgram);
    float size = disSize(gen);
    torus->setScale(size, size, size);
    torus->translate(disX(gen), disY(gen), disZ(gen));
    scene->addChild(torus);
    gc.torusVector.emplace_back(torus);
}

void MainWidget::initShaders()
{
        // Compile vertex shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
            close();
        // Compile fragment shader
        if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
            close();
        // Link shader pipeline
        if (!program.link())
            close();

        // Compile vertex shader
        if (!particlesProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/prvshader.glsl"))
            close();
        // Compile fragment shader
        if (!particlesProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/prfshader.glsl"))
            close();
        // Link shader pipeline
        if (!particlesProgram.link())
            close();

        // Compile vertex shader
        if (!modelProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/modelvshader.glsl"))
            close();
        // Compile fragment shader
        if (!modelProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/modelfshader.glsl"))
            close();
        // Link shader pipeline
        if (!modelProgram.link())
            close();

        // Compile vertex shader
        if (!sbProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/sbvshader.glsl"))
            close();
        // Compile fragment shader
        if (!sbProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/sbfshader.glsl"))
            close();
        // Link shader pipeline
        if (!sbProgram.link())
            close();
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    const qreal zNear = 0.3, zFar = 2000.0, fov = 45.0;
    // Reset projection
    projection.setToIdentity();
    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    //delta time
    float currentFrame = QTime::currentTime().msecsSinceStartOfDay();
    if(lastFrame == 0.0)
        lastFrame = currentFrame;
    deltaTime = (currentFrame - lastFrame) / 1000.0;
    lastFrame = currentFrame;
    //torus generation
    torrusTime += deltaTime;
    if(torrusTime >= 3.0f) {
        generateTorus();
        torrusTime = 0.0f;
    }
    Light dirLight(QVector3D(0.0, -1.0, 0.5));
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Calculate model view transformation
    QMatrix4x4 matrix;
   /* if(orbit) {
        camera.orbitAround(matrix, 1.0f , 0.0f);
    }*/
    Camera *cam = static_cast<Camera*>(camera.get());
    cam->lookAt(matrix);
    Renderer *renderer = new Renderer(dirLight);
    renderer->_projection = projection;
    renderer->_view = matrix;
    renderer->camPos = camera->getPos();
    Terrain *t = static_cast<Terrain*>(terrain.get());
    renderer->mapSize = t->getSize();
    renderer->mapNbV = t->getSizeV();
    particleEngineBullet->updateParticles();
    particleEngineBullet->drawParticles(*renderer);
    scene->draw(*renderer);
    t->moveTerrain();
   // gc.checkCollisionTorus(jet, scene);
    gc.moveTorus(scene);
    delete renderer;
}
