#ifndef TERRAIN_H
#define TERRAIN_H

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <QOpenGLShaderProgram>
#include <noise/noise.h>
#include <QTimer>
#include "gameobject.h"
#include "mesh.h"
#include "seasonmanager.h"
#include "particleengine.h"

class Chunk : public GameObject
{
public:
    Chunk(std::vector<Texture> &textures, QOpenGLShaderProgram &program, QOpenGLShaderProgram &particlesProgram);
    Chunk(int size, int nbV, int startX, int startZ,int decalage, std::vector<Texture> &textures, QOpenGLShaderProgram &program, QOpenGLShaderProgram &particlesProgram);

    int getSize();
    int getSizeV();
    void draw(Renderer &renderer) override;
    void setInitPos(float x, float y, float z);

private:
    std::unique_ptr<Mesh> _mesh;
    QOpenGLShaderProgram &_program;
    ParticleEngine _pEngine;
    int sizeV, size, decalage, startX, startZ;
    QVector3D initPos;

    void generateTerrain(std::vector<Texture> &textures);
};

class Terrain : public GameObject {
public:
    Terrain(int chunkSize, int chunkNbV, QOpenGLShaderProgram &program, QOpenGLShaderProgram &particlesProgram)
        : _chunkSize(chunkSize), _chunkNbV(chunkNbV), _boxDecalage(5), _startX(10), _startZ(20), _program(program), _pProgram(particlesProgram)
    {
        textures = loadTextures();
        seasonM = new SeasonManager(Seasons::Summer);
        seasonTimer.connect(&seasonTimer, SIGNAL(timeout()), seasonM, SLOT(changeSeason()));
        seasonTimer.start(SEASON_DURATION);
    }

    void draw(Renderer &renderer) override;
    int getSize();
    int getSizeV();
    void addChunk(float _x, float _y, float _z);
    void moveTerrain();
private:
    std::list<Chunk> _chunks;
    std::vector<Texture> textures;
    QOpenGLShaderProgram &_program, &_pProgram;
    int _chunkSize, _chunkNbV;
    int _boxDecalage;
    int _startX, _startZ;
    QTimer seasonTimer;
    SeasonManager *seasonM;
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

#endif // TERRAIN_H
