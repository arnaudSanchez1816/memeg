QT       += core gui widgets

TARGET = plane
TEMPLATE = app

INCLUDEPATH += $$PWD/external/include
LIBS += -L$$PWD/external/bin -L$$PWD/external/lib -lassimp

SOURCES += main.cpp \
    camera.cpp \
    seasonmanager.cpp \
    particle.cpp \
    particleengine.cpp \
    utils.cpp \
    mesh.cpp \
    model.cpp \
    Voxel.cpp \
    voxel.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    camera.h \
    seasonmanager.h \
    particle.h \
    particleengine.h \
    utils.h \
    mesh.h \
    model.h \
    Voxel.h \
    voxel.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

CONFIG += c++14


# install
target.path = .
INSTALLS += target

DISTFILES += \
    assets/nanosuit/nanosuit2.c4d \
    assets/nanosuit/back.jpg \
    assets/nanosuit/front.jpg \
    assets/nanosuit/nanosuit2.jpg \
    assets/nanosuit/perpective.jpg \
    assets/nanosuit/wallpap.jpg \
    assets/nanosuit/tex/arm_dif.png \
    assets/nanosuit/tex/arm_showroom_ddn.png \
    assets/nanosuit/tex/arm_showroom_spec.png \
    assets/nanosuit/tex/body_dif.png \
    assets/nanosuit/tex/body_showroom_ddn.png \
    assets/nanosuit/tex/body_showroom_spec.png \
    assets/nanosuit/tex/cell_arm_alpha.png \
    assets/nanosuit/tex/cell_body_alpha.png \
    assets/nanosuit/tex/cell_ddn.png \
    assets/nanosuit/tex/cell_hand_alpha.png \
    assets/nanosuit/tex/cell_helmet_alpha.png \
    assets/nanosuit/tex/cell_leg_alpha.png \
    assets/nanosuit/tex/glass_ddn.png \
    assets/nanosuit/tex/glass_dif.png \
    assets/nanosuit/tex/hand_dif.png \
    assets/nanosuit/tex/hand_showroom_ddn.png \
    assets/nanosuit/tex/hand_showroom_spec.png \
    assets/nanosuit/tex/helmet_dif.png \
    assets/nanosuit/tex/helmet_showroom_ddn.png \
    assets/nanosuit/tex/helmet_showroom_spec.png \
    assets/nanosuit/tex/leg_dif.png \
    assets/nanosuit/tex/leg_showroom_ddn.png \
    assets/nanosuit/tex/leg_showroom_spec.png \
    assets/nanosuit/nanosuit2.3ds \
    assets/nanosuit/nanosuit2.obj
