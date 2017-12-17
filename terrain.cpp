#include "terrain.h"
#include <iostream>
#include "noiseutils.h"

using namespace noise;

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
            vertex._tangent = QVector3D();
            vertex._normal = QVector3D();
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
    generateTerrain(textures, cptId); // generate heightmap
    for(auto it = texturesPath.begin(); it != texturesPath.end(); ++it) {
        Texture texture;
        QOpenGLTexture *tex = new QOpenGLTexture(QImage(it->first.c_str()).mirrored());
        tex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        tex->setMagnificationFilter(QOpenGLTexture::NearestMipMapNearest);
        tex->setWrapMode(QOpenGLTexture::Repeat);
        tex->generateMipMaps();
        tex->bind();
        float aniso = 2.0;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
        tex->release();
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

void Terrain::generateTerrain(std::vector<Texture> &textures, int &cptId) {
    //https://www.redblobgames.com/maps/terrain-from-noise/
    //http://libnoise.sourceforge.net/tutorials/tutorial3.html
    module::RidgedMulti mountainTerrain;
    module::Billow baseFlatTerrain;
    module::ScaleBias flatTerrain;
    module::Perlin terrainType;
    module::Select terrainSelector;
    module::Turbulence finalTerrain;
    mountainTerrain.SetOctaveCount(4);
    baseFlatTerrain.SetFrequency(2.0);
    flatTerrain.SetSourceModule(0, baseFlatTerrain);
    flatTerrain.SetScale(0.125);
    flatTerrain.SetBias(-0.75);
    terrainType.SetFrequency(0.5);
    terrainType.SetPersistence(0.25);
    terrainSelector.SetSourceModule (0, flatTerrain);
    terrainSelector.SetSourceModule (1, mountainTerrain);
    terrainSelector.SetControlModule(terrainType);
    terrainSelector.SetBounds (0.0, 1000.0);
    terrainSelector.SetEdgeFalloff (0.2);
    finalTerrain.SetSourceModule (0, terrainSelector);
    finalTerrain.SetFrequency (2.0);
    finalTerrain.SetPower (0.25);
    utils::NoiseMap heightMap;
    utils::NoiseMapBuilderPlane heightMapBuilder;
    heightMapBuilder.SetSourceModule(finalTerrain);
    heightMapBuilder.SetDestNoiseMap(heightMap);
    heightMapBuilder.SetDestSize(256, 256);
    heightMapBuilder.SetBounds(10.0,15.0, 20.0, 30.0);
    heightMapBuilder.Build();
    std::vector<unsigned char> data;
    int OldRange = (1.0 - -1.0);
    int NewRange = (255 - 0);
    for(int y = 0; y < 256; ++y) {
        for(int x = 0; x < 256; ++x) {
            float val = std::max(std::min(heightMap.GetValue(x, y), 1.0f), -1.0f);
            int NewValue = (((val - -1.0) * NewRange) / OldRange);
            data.push_back((unsigned char) NewValue);
            data.push_back((unsigned char) NewValue);
            data.push_back((unsigned char) NewValue);
        }
    }
    QImage img(data.data(), 256, 256, QImage::Format_RGB888);
    QOpenGLTexture *tex = new QOpenGLTexture(img);
    tex->setMinificationFilter(QOpenGLTexture::Linear);
    tex->setMagnificationFilter(QOpenGLTexture::Linear);
    Texture te;
    te.id = cptId++;
    //te.path = it->first;
    te.type = Mesh::DIFFUSE_MAP;
    te.uniformName = "height_map";
    te.texture = tex;
    textures.push_back(te);
}
