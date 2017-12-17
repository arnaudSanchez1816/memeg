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
