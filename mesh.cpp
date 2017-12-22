#include "mesh.h"
#include <iostream>

const std::string Mesh::DIFFUSE_MAP = "texture_diffuse";
const std::string Mesh::SPECULAR_MAP = "texture_specular";
const std::string Mesh::NORMAL_MAP = "texture_normal";

Mesh::~Mesh()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    vao.destroy();
}

void Mesh::setupMesh(QOpenGLShaderProgram &_program) {
    if(_indices.size() > 0) {
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
        //vertex tangent
        int tangentLocation = _program.attributeLocation("a_tangent");
        _program.enableAttributeArray(tangentLocation);
        _program.setAttributeBuffer(tangentLocation, GL_FLOAT, (int) offsetof(Vertex, _tangent), 3, sizeof(Vertex));
        //vertex texture coords
        int texcoordLocation = _program.attributeLocation("a_texcoord");
        _program.enableAttributeArray(texcoordLocation);
        _program.setAttributeBuffer(texcoordLocation, GL_FLOAT, (int) offsetof(Vertex, _texCoords), 2, sizeof(Vertex));
        vao.release();
    } else {
        vao.bind();
        arrayBuf.bind();
        arrayBuf.allocate(_vertices.data(), _vertices.size() * sizeof(Vertex));
        //vertex positions
        int vertexLocation = _program.attributeLocation("a_position");
        _program.enableAttributeArray(vertexLocation);
        _program.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(Vertex));
        //vertex normals
        int normalLocation = _program.attributeLocation("a_normal");
        _program.enableAttributeArray(normalLocation);
        _program.setAttributeBuffer(normalLocation, GL_FLOAT, (int) offsetof(Vertex, _normal), 3, sizeof(Vertex));
        //vertex tangent
        int tangentLocation = _program.attributeLocation("a_tangent");
        _program.enableAttributeArray(tangentLocation);
        _program.setAttributeBuffer(tangentLocation, GL_FLOAT, (int) offsetof(Vertex, _tangent), 3, sizeof(Vertex));
        //vertex texture coords
        int texcoordLocation = _program.attributeLocation("a_texcoord");
        _program.enableAttributeArray(texcoordLocation);
        _program.setAttributeBuffer(texcoordLocation, GL_FLOAT, (int) offsetof(Vertex, _texCoords), 2, sizeof(Vertex));
        vao.release();
    }
}

void Mesh::draw(QOpenGLShaderProgram &_program) {
    if(_indices.size() > 0) {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        int i = 0;
        vao.bind();
        for(auto t = _textures.begin(); t != _textures.end(); ++t, ++i) {
            std::string number;
            std::string name = t->type;
            if(name == DIFFUSE_MAP) {
                number = std::to_string(diffuseNr++);
            } else if(name == SPECULAR_MAP) {
                number = std::to_string(specularNr++);
            } else if(name == NORMAL_MAP) {
                number = std::to_string(normalNr++);
            }
            t->texture->bind(t->id);
            std::string v = name + number;
            if(t->uniformName != "") {
                _program.setUniformValue(t->uniformName.c_str(), t->id);
            } else {
                _program.setUniformValue(v.c_str(), t->id);
            }
        }
        auto check = [] (unsigned int i) {
            return i > 1;
        };
        _program.setUniformValue("useSpecular", check(specularNr));
        _program.setUniformValue("useNormal", check(normalNr));
        glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
        vao.release();
    } else {
        unsigned int diffuseNr = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr = 1;
        int i = 0;
        vao.bind();
        for(auto t = _textures.begin(); t != _textures.end(); ++t, ++i) {
            std::string number;
            std::string name = t->type;
            if(name == DIFFUSE_MAP) {
                number = std::to_string(diffuseNr++);
            } else if(name == SPECULAR_MAP) {
                number = std::to_string(specularNr++);
            } else if(name == NORMAL_MAP) {
                number = std::to_string(normalNr++);
            }
            t->texture->bind(t->id);
            std::string v = name + number;
            if(t->uniformName != "") {
                _program.setUniformValue(t->uniformName.c_str(), t->id);
            } else {
                _program.setUniformValue(v.c_str(), t->id);
            }
        }
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
        vao.release();
    }
}
/*
bool Mesh::collide(Mesh &m) {
    return (_collisionBox.front().x() <= m._collisionBox.back().x() and _collisionBox.back().x() >= m._collisionBox.front().x()) and
           (_collisionBox.front().y() <= m._collisionBox.back().y() and _collisionBox.back().y() >= m._collisionBox.front().y()) and
           (_collisionBox.front().z() <= m._collisionBox.back().z() and _collisionBox.back().z() >= m._collisionBox.front().z());
}
*/
