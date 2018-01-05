#ifndef RENDERER_H
#define RENDERER_H

#include <QMatrix4x4>
#include <QVector3D>
#include <vector>
#include "light.h"

class Renderer
{
public:
    QVector3D camPos;
    QMatrix4x4 _projection, _view;
    Light &light;
    int mapSize, mapNbV;
    int winter;

    Renderer(Light &light)
        :light(light) {

    }
};

#endif // RENDERER_H
