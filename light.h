#ifndef LIGHT_H
#define LIGHT_H

#include <QVector3D>

class Light
{
public:
    QVector3D _pos;
    QVector3D _ambient, _diffuse, _specular;
    Light(QVector3D pos)
        :_pos(pos), _ambient(0.1, 0.1, 0.1), _diffuse(1.0, 1.0, 1.0), _specular(1.0, 1.0, 1.0){}
};

#endif // LIGHT_H
