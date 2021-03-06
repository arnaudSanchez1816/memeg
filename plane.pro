QT += core gui widgets multimedia multimediawidgets

TARGET = plane
TEMPLATE = app

INCLUDEPATH += $$PWD/external/include
LIBS += -L$$PWD/external/bin -L$$PWD/external/lib -lassimp -lnoise -lnoiseutils

SOURCES += main.cpp \
    camera.cpp \
    seasonmanager.cpp \
    particle.cpp \
    particleengine.cpp \
    utils.cpp \
    mesh.cpp \
    model.cpp \
    gameobject.cpp \
    terrain.cpp \
    light.cpp \
    scene.cpp \
    skybox.cpp \
    renderer.cpp \
    gamecontroller.cpp

SOURCES += \
    mainwidget.cpp

HEADERS += \
    mainwidget.h \
    camera.h \
    seasonmanager.h \
    particle.h \
    particleengine.h \
    utils.h \
    mesh.h \
    model.h \
    gameobject.h \
    terrain.h \
    light.h \
    scene.h \
    skybox.h \
    renderer.h \
    gamecontroller.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

CONFIG += c++14


# install
target.path = .
INSTALLS += target

