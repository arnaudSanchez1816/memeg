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
#include "utils.h"

MainWidget::MainWidget(int fps, Seasons s, QWidget *parent) :
    QOpenGLWidget(parent),
    model(nullptr),
    terrain(nullptr),
    camera(),
    orbit(false),
    fps(fps),
    particleEngineSnow(nullptr),
    particleEngineRain(nullptr)
{
    setMouseTracking(true);
    seasonTimer = new QTimer();
    seasonM = new SeasonManager(s);
    seasonTimer->connect(seasonTimer, SIGNAL(timeout()), seasonM, SLOT(changeSeason()));
    seasonTimer->start(CALENDAR_TIME);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete terrain;
    delete height;
    delete particleEngineSnow;
    delete particleEngineRain;
    delete model;
    doneCurrent();
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    // Save mouse press position
    mousePressPosition = QVector2D(e->localPos());
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::RightButton) {
        orbit = !orbit;
    }
}

void MainWidget::wheelEvent(QWheelEvent *event) {
}

void MainWidget::timerEvent(QTimerEvent *)
{
    update();
}

void MainWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        case Qt::Key_Z:
            camera.processKeyPress(Camera_Movement::Z);
            break;
        case Qt::Key_S:
            camera.processKeyPress(Camera_Movement::S);
            break;
        case Qt::Key_Q:
            camera.processKeyPress(Camera_Movement::Q);
            break;
        case Qt::Key_D:
            camera.processKeyPress(Camera_Movement::D);
            break;
        case Qt::Key_C:
            camera.processKeyPress(Camera_Movement::C);
            break;
        case Qt::Key_W:
            camera.processKeyPress(Camera_Movement::W);
            break;
    }
}

void MainWidget::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton) {
        float xoffset = event->x() - mousePressPosition.x();
        float yoffset = mousePressPosition.y() - event->y(); // reversed since y-coordinates range from bottom to top
        mousePressPosition = QVector2D(event->localPos());
        camera.processMouseMovement(xoffset, yoffset);
    }
}

void MainWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);
    initTextures();
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    // Enable back face culling
    //glEnable(GL_CULL_FACE);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    terrain = new Terrain(100, 400, program);
    particleEngineRain = new ParticleEngine(ParticleType::Rain);
    particleEngineSnow = new ParticleEngine(ParticleType::Snow);
    model = new Model("assets/nanosuit/nanosuit.obj", &modelProgram);
    //model = new Model("assets/ship/SciFi_Fighter_AK5.obj", &modelProgram);
    //model = new Model("assets/plane/Wraith Raider Starship.obj", &modelProgram);
    //model->setScale(0.001, 0.001, 0.001);
    //model->rotateY(-90);
    // Use QBasicTimer because its faster than QTimer
    timer.start(1000/fps, this);
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
}

void MainWidget::initTextures()
{
    // Load heightmap and cube.png image
    height = new QOpenGLTexture(QImage(":/heightmap-1.png").mirrored());

    // Set nearest filtering mode for texture minification
    height->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    height->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    height->setWrapMode(QOpenGLTexture::Repeat);
}

void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 0.3, zFar = 500.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MainWidget::paintGL()
{
    Light dirLight(QVector3D(0.5, -0.4, -0.2));
    auto lerp = [] (QColor &&a, QColor &&b, float step) {
        float h = a.redF() * (1.0 - step) + b.redF() * step;
        float s = a.greenF() * (1.0 - step) + b.greenF() * step;
        float v = a.blueF() * (1.0 - step) + b.blueF() * step;
        return QColor::fromRgbF(h, s, v);
    };
    //QColor color = LerpHSV(seasonM->getCurrentSeasonColor().toHsv(), seasonM->getNextSeasonColor().toHsv(), 1.0 - (seasonTimer->remainingTime() /(float) CALENDAR_TIME));
    QColor color = lerp(seasonM->getCurrentSeasonColor(), seasonM->getNextSeasonColor(),1.0 - (seasonTimer->remainingTime() / (float) CALENDAR_TIME));
    //dirLight._diffuse = QVector3D(color.redF(), color.greenF(), color.blueF()).normalized(); //lol
    glClearColor(color.redF(), color.greenF(), color.blueF(), 1);
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Calculate model view transformation
    QMatrix4x4 matrix;
    if(orbit) {
        camera.orbitAround(matrix, 1.0f , 0.0f);
    }
    camera.lookAt(matrix);
    program.bind();
    program.setUniformValue("mvp_matrix", projection * matrix);
    program.setUniformValue("dirLight.sunDirection", dirLight._pos);
    program.setUniformValue("dirLight.ambient", dirLight._ambient);
    program.setUniformValue("dirLight.diffuse", dirLight._diffuse);
    program.setUniformValue("dirLight.specular", dirLight._specular);
    if(seasonM->getSeason() == Seasons::Winter) {
        terrain->draw(program, 1);
    } else {
        terrain->draw(program, 0);
    }
    particlesProgram.bind();
    height->bind(0);
    particlesProgram.setUniformValue("height_map", 0);
    particlesProgram.setUniformValue("mvp_matrix", projection * matrix);
    particlesProgram.setUniformValue("map_size", terrain->getSize());
    if(seasonM->getSeason() == Seasons::Winter) {
        ParticleEngine &pe = *particleEngineSnow;
        pe.generateParticles(terrain->getSize(), 400.0f);
        pe.updateParticles();
        pe.drawParticles(&particlesProgram);
    } else if(seasonM->getSeason() == Seasons::Autumn) {
        ParticleEngine &pe = *particleEngineRain;
        pe.generateParticles(terrain->getSize(), 2000.0f);
        pe.updateParticles();
        pe.drawParticles(&particlesProgram);
    }
    height->release();
    modelProgram.bind();
    modelProgram.setUniformValue("viewpos", camera.getPos());
    modelProgram.setUniformValue("mvp_matrix", projection * matrix);
    modelProgram.setUniformValue("dirLight.sunDirection", dirLight._pos);
    modelProgram.setUniformValue("dirLight.ambient", dirLight._ambient);
    modelProgram.setUniformValue("dirLight.diffuse", dirLight._diffuse);
    modelProgram.setUniformValue("dirLight.specular", dirLight._specular);
    model->draw();
}
