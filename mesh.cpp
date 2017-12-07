#include "mesh.h"
#include <iostream>

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    vao.destroy();
}

void Mesh::setupMesh(QOpenGLShaderProgram &_program) {
    vao.bind();
    arrayBuf.bind();
    arrayBuf.allocate(_vertices.data(), _vertices.size() * sizeof(Vertex));
    indexBuf.bind();
    indexBuf.allocate(_indices.data(), _indices.size() * sizeof(unsigned int));
    //vertex positions
    int vertexLocation = _program.attributeLocation("a_position");
    _program.enableAttributeArray(vertexLocation);
    _program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(Vertex));
    //vertex normals
    int normalLocation = _program.attributeLocation("a_normal");
    _program.enableAttributeArray(normalLocation);
    _program.setAttributeBuffer(normalLocation, GL_FLOAT, (int) offsetof(Vertex, _normal), 3, sizeof(Vertex));
    //vertex texture coords
    int texcoordLocation = _program.attributeLocation("a_texcoord");
    _program.enableAttributeArray(texcoordLocation);
    _program.setAttributeBuffer(texcoordLocation, GL_FLOAT, (int) offsetof(Vertex, _texCoords), 2, sizeof(Vertex));
    vao.release();
}

void Mesh::draw(QOpenGLShaderProgram &_program) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    int i = 0;
    vao.bind();
    for(auto t = _textures.begin(); t != _textures.end(); ++t, ++i) {
        std::string number;
        std::string name = t->type;
        if(name == "texture_diffuse") {
            number = std::to_string(diffuseNr++);
        } else if(name == "texture_specular") {
            number = std::to_string(specularNr++);
        }
        t->texture->bind(t->id);
        std::string v = name + number;
        _program.setUniformValue(v.c_str(), t->id);
    }
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    vao.release();
}
