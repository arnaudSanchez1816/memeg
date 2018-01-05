#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <string>
#include <vector>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions_4_2_Core>
#include <assimp/Importer.hpp>
#include <QOpenGLTexture>
#include <memory>

struct Vertex {
    QVector3D _position;
    QVector3D _normal, _tangent;
    QVector2D _texCoords;
    bool _isTop;
};

struct Texture {
    QOpenGLTexture *texture;
    unsigned int id;
    std::string type;
    std::string uniformName;
    aiString path;
};

class Mesh : protected QOpenGLFunctions_4_2_Core
{
public:
    const static std::string DIFFUSE_MAP;
    const static std::string SPECULAR_MAP;
    const static std::string NORMAL_MAP;

    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _textures;
    std::vector<QVector3D> _collisionBox;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, QOpenGLShaderProgram &program)
        : _vertices(vertices), _indices(indices), _textures(textures), arrayBuf(QOpenGLBuffer::VertexBuffer), indexBuf(QOpenGLBuffer::IndexBuffer)
    {
        initializeOpenGLFunctions();
        vao.create();
        arrayBuf.create();
        indexBuf.create();
        setupMesh(program);
        /*
        //collision box
        float minX = 0, minY = 0, minZ = 0;
        float maxX =  0, maxY = 0, maxZ = 0;
        for(int i = 0; i < _vertices.size(); ++i){
            const QVector3D &pos = _vertices[i]._position;
            minX = std::min(pos.x(), minX);
            minY = std::min(pos.y(), minY);
            minZ = std::min(pos.z(), minZ);

            maxX = std::max(pos.x(), maxX);
            maxY = std::max(pos.y(), maxY);
            maxZ = std::max(pos.z(), maxZ);
        }
        QVector3D min(minX, minY, minZ);
        QVector3D max(maxX, maxY, maxZ);

        _collisionBox.push_back(min);
        _collisionBox.push_back(max);
        */
    }
    void draw(QOpenGLShaderProgram &_program);
    //bool collide(Mesh &m);
    virtual ~Mesh();

private:
    // render data
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    void setupMesh(QOpenGLShaderProgram &_program);
};

#endif // MESH_H
