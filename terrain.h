#ifndef TERRAIN_H
#define TERRAIN_H

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <QOpenGLShaderProgram>
#include <noise/noise.h>
#include "gameobject.h"
#include "mesh.h"

class Chunk : public GameObject
{
public:
    Chunk(std::vector<Texture> &textures, QOpenGLShaderProgram &program);
    Chunk(int size, int nbV, int startX, int startZ,int decalage, std::vector<Texture> &textures, QOpenGLShaderProgram &program);

    void draw(QOpenGLShaderProgram &program, int winter);
    int getSize();
    int getSizeV();
private:
    std::unique_ptr<Mesh> _mesh;
    int sizeV, size, decalage, startX, startZ;

    void generateTerrain(std::vector<Texture> &textures, int cptId);
};

#endif // TERRAIN_H

class Terrain{
public:
    Terrain(int chunkSize, int chunkNbV, QOpenGLShaderProgram &program)
        : _chunkSize(chunkSize), _chunkNbV(chunkNbV), _boxDecalage(5), _startX(10), _startZ(20)
    {
        textures = loadTextures();
        _chunks.emplace_back(_chunkSize, _chunkNbV, _startX, _startZ, _boxDecalage, textures,program);
        _startZ += _boxDecalage;
        _chunks.emplace_back(_chunkSize, _chunkNbV, _startX, _startZ, _boxDecalage, textures,program);
        Chunk &c = _chunks.back();
        float transla = ((chunkNbV - 1.0) /(float) chunkNbV) * (float) chunkSize;
        c.translate(0.0f, 0.0f, chunkSize);
    }

    void draw(QOpenGLShaderProgram &program, int winter = 0);
    int getSize();
    int getSizeV();
private:
    std::list<Chunk> _chunks;
    std::vector<Texture> textures;
    int _chunkSize, _chunkNbV;
    int _boxDecalage;
    int _startX, _startZ;
    const std::map<std::string, std::string> texturesPath{
        //{":/heightmap-1.png", "height_map"},
        {":/sand.jpg", "sand"},
        {":/rock.jpg", "rock"},
        {":/snow_rock.jpg", "winter_rock"},
        {":/snow_sand.jpg", "winter_sand"},
        {":/sand_n.png", "sand_n"},
        {":/rock_n.png", "rock_n"},
        {":/snow_rock_n.png", "winter_rock_n"},
        {":/snow_sand_n.png", "winter_sand_n"},
    };


    std::vector<Texture> loadTextures();
};
