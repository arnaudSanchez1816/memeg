#include "terrain.h"
#include <iostream>
#include "noiseutils.h"
#include "mainwidget.h"

using namespace noise;

Chunk::Chunk(std::vector<Texture> &textures, QOpenGLShaderProgram &program, QOpenGLShaderProgram &particlesProgram)
    : Chunk(50, 150, 10, 20, 10, textures, program, particlesProgram) {}

Chunk::Chunk(int size, int nbV, int startX, int startY, int decalage, std::vector<Texture> &textures, QOpenGLShaderProgram &program, QOpenGLShaderProgram &particlesProgram)
    : sizeV(nbV), size(size), decalage(decalage), startX(startX), startZ(startY), _program(program), _pEngine(ParticleType::Snow, particlesProgram)
{
    const float nbVf = nbV;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    // creation des vertices
    //float map_size = size;
    for(int y= 0; y < nbV; ++y) {
        for(int x = 0; x < nbV; ++x) {
            Vertex vertex;
            vertex._position =  QVector3D((x / (nbVf - 1)) * size, 0.0f, (y / (nbVf - 1)) * size);
            vertex._texCoords = QVector2D(x / (nbVf - 1), y / (nbVf - 1));
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
    generateTerrain(textures/*, 0*/); // generate heightmap
    _mesh = std::make_unique<Mesh>(vertices, indices, textures, program);
}

int Chunk::getSize() {
    return size;
}

int Chunk::getSizeV() {
    return sizeV;
}

void Chunk::setInitPos(float x, float y, float z) {
    initPos = QVector3D(x, y, z);
    translate(x, y, z);
}

void Chunk::generateTerrain(std::vector<Texture> &textures/*, int cptId*/) {
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
    std::vector<unsigned char> data;
    int OldRange = (1.0 - -1.0);
    int NewRange = (255 - 0);
    double stX, stZ;
    stX = startX;
    stZ = startZ;
    for(int y = 0; y < 256; ++y) {
        double decalZ = ((y / (255.0)) *(double) decalage);
        for(int x = 0; x < 256; ++x) {
            double decalX = ((x / (255.0)) *(double) decalage);
            double valN = finalTerrain.GetValue(stX + decalX, 0.0, stZ + decalZ);
            float val = std::max(std::min(valN, 1.0), -1.0);
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
    tex->setWrapMode(QOpenGLTexture::ClampToEdge);
    Texture te;
    //te.id = cptId++;
    te.id = tex->textureId();
    //te.path = it->first;
    te.type = Mesh::DIFFUSE_MAP;
    te.uniformName = "height_map";
    te.texture = tex;
    textures.push_back(te);
}

int Terrain::getSize() {
    return _chunkSize;
}

int Terrain::getSizeV() {
    return _chunkNbV;
}

std::vector<Texture> Terrain::loadTextures() {
    std::vector<Texture> textures;
    //int cptId = 1;
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
        //texture.id = cptId++;
        texture.id = tex->textureId();
        texture.path = it->first;
        texture.type = Mesh::DIFFUSE_MAP;
        texture.uniformName = it->second;
        texture.texture = tex;
        textures.push_back(texture);
    }
    return textures;
}

void Chunk::draw(Renderer &renderer){
     _program.bind();
     _program.setUniformValue("mvp_matrix", renderer._projection * renderer._view);
     _program.setUniformValue("dirLight.sunDirection", renderer.light._pos);
     _program.setUniformValue("dirLight.ambient", renderer.light._ambient);
     _program.setUniformValue("dirLight.diffuse", renderer.light._diffuse);
     _program.setUniformValue("dirLight.specular", renderer.light._specular);
    _program.setUniformValue("winter", renderer.winter);
    _program.setUniformValue("sizeV", (float) sizeV);
    _program.setUniformValue("transform", _transform);
    _mesh->draw(_program);
    if(renderer.winter == 1) {
        _pEngine.generateParticles(renderer.mapSize, 100.0f);
        _pEngine.updateParticles();
        _pEngine.drawParticles(renderer, _mesh->_textures.front().texture);
    }
    drawChild(renderer);
}

void Terrain::draw(Renderer &renderer) {
    int winter;
    if(seasonM->getSeason() == Seasons::Winter) {
        winter = 1;
    } else {
        winter = 0;
    }
    renderer.winter = winter;
    drawChild(renderer);
}

void Terrain::addChunk(float _x, float _y, float _z) {
    //_chunks.emplace_back(_chunkSize, _chunkNbV, _startX, _startZ, _boxDecalage, textures,program);
    std::shared_ptr<GameObject> c = std::make_shared<Chunk>(_chunkSize, _chunkNbV, _startX, _startZ, _boxDecalage, textures, _program, _pProgram);
    addChild(c);
    Chunk *ch = static_cast<Chunk*>(c.get());
    ch->setInitPos(_x, _y, _z);
    _startZ += _boxDecalage;
}

void Terrain::moveTerrain() {
    float speed = 30.0 * MainWidget::deltaTime;
    for(auto &c : getChildren()) {
        QVector3D pos = c->getPos();
        c->translate(0.0, 0.0, pos.z() - speed);
    }
    auto &c = getChildren().front();
    auto &cL = getChildren().back();
    if(c->getPos().z() < - _chunkSize) {
        this->removeChild(c);
        float cLZ = cL->getPos().z();
        addChunk(0.0, 0.0, _chunkSize + cLZ);
    }
}
