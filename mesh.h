#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <string>
#include <vector>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include <assimp/Importer.hpp>
#include <QOpenGLTexture>
#include <memory>

struct Vertex {
    QVector3D _position;
    QVector3D _normal;
    QVector2D _texCoords;
};

struct Texture {
    QOpenGLTexture *texture;
    unsigned int id;
    std::string type;
    aiString path;
};

class Mesh : protected QOpenGLFunctions
{
public:
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, QOpenGLShaderProgram &program)
        : _vertices(vertices), _indices(indices), _textures(textures), arrayBuf(QOpenGLBuffer::VertexBuffer), indexBuf(QOpenGLBuffer::IndexBuffer)
    {
        initializeOpenGLFunctions();
        vao.create();
        arrayBuf.create();
        indexBuf.create();
        setupMesh(program);
    }
    void draw(QOpenGLShaderProgram &_program);
    virtual ~Mesh();

private:
    // render data
    QOpenGLVertexArrayObject vao;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    void setupMesh(QOpenGLShaderProgram &_program);
};

#endif // MESH_H
