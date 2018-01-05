#ifndef VMESH_H
#define VMESH_H

#include <QVector3D>
#include <memory>
#include "mesh.h"

class VMesh
{
public:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    VMesh(float x, float y, float z);

};

#endif // VMESH_H
