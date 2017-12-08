#include "terrain.h"

Terrain::Terrain(QOpenGLShaderProgram &program)
    : Terrain(50, 150, program) {}

Terrain::Terrain(int size, int nbV, QOpenGLShaderProgram &program)
    : sizeV(nbV), size(size)
{
    const float nbVf = nbV;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    // creation des vertices
    //float map_size = size;
    for(int y= 0; y < nbV; ++y) {
        for(int x = 0; x < nbV; ++x) {
            Vertex vertex;
            vertex._position =  QVector3D((x / nbVf) * size, 0.0f, (y / nbVf) * size);
            vertex._texCoords = QVector2D(x / nbVf, y / nbVf);
            vertices.emplace_back(vertex);
        }
    }
    //init tableau indices
    for(int y= 0; y < (nbV - 1); ++y) {
        for(int x = 0; x < (nbV - 1); ++x) {
            indices.push_back((y*nbV) + x);
            indices.push_back((y*nbV) + x + 1);
            indices.push_back((y*nbV) + x + nbV);
            indices.push_back((y*nbV) + x + 1);
            indices.push_back((y*nbV) + x + nbV + 1);
            indices.push_back((y*nbV) + x + nbV);
        }
    }
    textures = loadTextures();
    _mesh = std::make_unique<Mesh>(vertices, indices, textures, program);
}

std::vector<Texture> Terrain::loadTextures() {
    std::vector<Texture> textures;
    int cptId = 0;
    for(auto it = texturesPath.begin(); it != texturesPath.end(); ++it) {
        Texture texture;
        QOpenGLTexture *tex = new QOpenGLTexture(QImage(it->first.c_str()).mirrored());
        tex->setMinificationFilter(QOpenGLTexture::Nearest);
        tex->setMagnificationFilter(QOpenGLTexture::Linear);
        tex->setWrapMode(QOpenGLTexture::Repeat);
        texture.id = cptId++;
        texture.path = it->first;
        texture.type = Mesh::DIFFUSE_MAP;
        texture.uniformName = it->second;
        texture.texture = tex;
        textures.push_back(texture);
    }
    return textures;
}

void Terrain::draw(QOpenGLShaderProgram &program, int winter = 0) {
    program.setUniformValue("winter", winter);
    program.setUniformValue("sizeV", (float) sizeV);
    _mesh->draw(program);
}

int Terrain::getSize() {
    return size;
}

int Terrain::getSizeV() {
    return sizeV;
}
