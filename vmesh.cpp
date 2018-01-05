#include "vmesh.h"

const std::vector<QVector3D> _pos = {
    QVector3D(-0.5, -0.5, 0.5),
    QVector3D(0.5, -0.5, 0.5),
    QVector3D(-0.5, 0.5, 0.5),
    QVector3D(0.5, 0.5, 0.5),
    QVector3D(-0.5, 0.5, -0.5),
    QVector3D(0.5, 0.5, -0.5),
    QVector3D(-0.5, -0.5, -0.5),
    QVector3D(0.5, -0.5,  -0.5)
};
const std::vector<QVector2D> _texCoords = {
    QVector2D(0.0, 0.0),
    QVector2D(1.0, 0.0),
    QVector2D(0.0, 1.0),
    QVector2D(1.0, 1.0)
};
const std::vector<QVector3D> _normals = {
    QVector3D(0.0,0.0, 1.0),
    QVector3D(0.0, 1.0, 0.0),
    QVector3D(0.0, 0.0, -1.0),
    QVector3D(0.0, -1.0, 0.0),
    QVector3D(1.0, 0.0, 0.0),
    QVector3D(-1.0, 0.0, 0.0)
};


VMesh::VMesh(float x, float y, float z)
{
    int cpt = 0;
    Vertex vertex;
    vertex._tangent = QVector3D();
    //f1
    //v1
    vertex._position = QVector3D(x + _pos[0].x(), y + _pos[0].y(), z + _pos[0].z());
    vertex._texCoords = _texCoords[0];
    vertex._normal = _normals[0];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v2
    vertex._position = QVector3D(x + _pos[1].x(), y + _pos[1].y(), z + _pos[1].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v3
    vertex._position = QVector3D(x + _pos[2].x(), y + _pos[2].y(), z + _pos[2].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v4
    vertex._position = QVector3D(x + _pos[2].x(), y + _pos[2].y(), z + _pos[2].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v5
    vertex._position = QVector3D(x + _pos[1].x(), y + _pos[1].y(), z + _pos[1].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v6
    vertex._position = QVector3D(x + _pos[3].x(), y + _pos[3].y(), z + _pos[3].z());
    vertex._texCoords = _texCoords[3];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //f2
    //v7
    vertex._position = QVector3D(x + _pos[2].x(), y + _pos[2].y(), z + _pos[2].z());
    vertex._texCoords = _texCoords[0];
    vertex._normal = _normals[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v8
    vertex._position = QVector3D(x + _pos[3].x(), y + _pos[3].y(), z + _pos[3].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v9
    vertex._position = QVector3D(x + _pos[4].x(), y + _pos[4].y(), z + _pos[4].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v10
    vertex._position = QVector3D(x + _pos[4].x(), y + _pos[4].y(), z + _pos[4].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v11
    vertex._position = QVector3D(x + _pos[3].x(), y + _pos[3].y(), z + _pos[3].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v12
    vertex._position = QVector3D(x + _pos[5].x(), y + _pos[5].y(), z + _pos[5].z());
    vertex._texCoords = _texCoords[3];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //f3
    //v13
    vertex._position = QVector3D(x + _pos[4].x(), y + _pos[4].y(), z + _pos[4].z());
    vertex._texCoords = _texCoords[3];
    vertex._normal = _normals[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v14
    vertex._position = QVector3D(x + _pos[5].x(), y + _pos[5].y(), z + _pos[5].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v15
    vertex._position = QVector3D(x + _pos[6].x(), y + _pos[6].y(), z + _pos[6].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v16
    vertex._position = QVector3D(x + _pos[6].x(), y + _pos[6].y(), z + _pos[6].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v17
    vertex._position = QVector3D(x + _pos[5].x(), y + _pos[5].y(), z + _pos[5].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v18
    vertex._position = QVector3D(x + _pos[7].x(), y + _pos[7].y(), z + _pos[7].z());
    vertex._texCoords = _texCoords[0];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //f4
    //v19
    vertex._position = QVector3D(x + _pos[6].x(), y + _pos[6].y(), z + _pos[6].z());
    vertex._texCoords = _texCoords[0];
    vertex._normal = _normals[3];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v20
    vertex._position = QVector3D(x + _pos[7].x(), y + _pos[7].y(), z + _pos[7].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v21
    vertex._position = QVector3D(x + _pos[0].x(), y + _pos[0].y(), z + _pos[0].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v22
    vertex._position = QVector3D(x + _pos[0].x(), y + _pos[0].y(), z + _pos[0].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v23
    vertex._position = QVector3D(x + _pos[7].x(), y + _pos[7].y(), z + _pos[7].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v24
    vertex._position = QVector3D(x + _pos[1].x(), y + _pos[1].y(), z + _pos[1].z());
    vertex._texCoords = _texCoords[3];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //f5
    //v25
    vertex._position = QVector3D(x + _pos[1].x(), y + _pos[1].y(), z + _pos[1].z());
    vertex._texCoords = _texCoords[0];
    vertex._normal = _normals[4];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v26
    vertex._position = QVector3D(x + _pos[7].x(), y + _pos[7].y(), z + _pos[7].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v27
    vertex._position = QVector3D(x + _pos[3].x(), y + _pos[3].y(), z + _pos[3].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v28
    vertex._position = QVector3D(x + _pos[3].x(), y + _pos[3].y(), z + _pos[3].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v29
    vertex._position = QVector3D(x + _pos[7].x(), y + _pos[7].y(), z + _pos[7].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v30
    vertex._position = QVector3D(x + _pos[5].x(), y + _pos[5].y(), z + _pos[5].z());
    vertex._texCoords = _texCoords[3];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //f6
    //v31
    vertex._position = QVector3D(x + _pos[6].x(), y + _pos[6].y(), z + _pos[6].z());
    vertex._texCoords = _texCoords[0];
    vertex._normal = _normals[5];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v32
    vertex._position = QVector3D(x + _pos[0].x(), y + _pos[0].y(), z + _pos[0].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v33
    vertex._position = QVector3D(x + _pos[4].x(), y + _pos[4].y(), z + _pos[4].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v34
    vertex._position = QVector3D(x + _pos[4].x(), y + _pos[4].y(), z + _pos[4].z());
    vertex._texCoords = _texCoords[2];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v35
    vertex._position = QVector3D(x + _pos[0].x(), y + _pos[0].y(), z + _pos[0].z());
    vertex._texCoords = _texCoords[1];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
    //v36
    vertex._position = QVector3D(x + _pos[2].x(), y + _pos[2].y(), z + _pos[2].z());
    vertex._texCoords = _texCoords[3];
    _vertices.push_back(vertex);
    _indices.push_back(cpt++);
}

/*
f 1/1/1 2/2/1 3/3/1
f 3/3/1 2/2/1 4/4/1
s 2
f 3/1/2 4/2/2 5/3/2
f 5/3/2 4/2/2 6/4/2
s 3
f 5/4/3 6/3/3 7/2/3
f 7/2/3 6/3/3 8/1/3
s 4
f 7/1/4 8/2/4 1/3/4
f 1/3/4 8/2/4 2/4/4
s 5
f 2/1/5 8/2/5 4/3/5
f 4/3/5 8/2/5 6/4/5
s 6
f 7/1/6 1/2/6 5/3/6
f 5/3/6 1/2/6 3/4/6
*/
