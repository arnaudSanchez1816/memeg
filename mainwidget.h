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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "camera.h"
#include "particleengine.h"
#include "model.h"
#include "terrain.h"
#include "light.h"
#include "renderer.h"
#include "scene.h"
#include "skybox.h"
#include "gamecontroller.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_2_Core>
#include <QMatrix4x4>
#include <QVector3D>
#include <QTime>
#include <QTimer>
#include <QElapsedTimer>
#include <QOpenGLShaderProgram>
#include <vector>

class GeometryEngine;

class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_2_Core
{
    Q_OBJECT

public:
    static float deltaTime, lastFrame;
    explicit MainWidget(int msFPS, QWidget *parent = 0);
    ~MainWidget();

    void generateTorus();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;
    void timerEvent(QTimerEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initShaders();

private:
    QBasicTimer timer;
    QMatrix4x4 projection;
    GameController gc;
    bool orbit;
    QVector2D mousePressPosition;
    int fov, fps;
    float torrusTime;
    ParticleEngine *particleEngineBullet;
    QVector3D lightPos;
    std::shared_ptr<GameObject> scene, model, jet, nano, skybox, terrain, camera;
    QOpenGLShaderProgram program, particlesProgram, modelProgram, sbProgram;
    std::vector<bool> keys;//0 Z, 1 Q, 2 S, 3 D, 4 Space

};

#endif // MAINWIDGET_H
