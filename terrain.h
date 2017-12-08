#ifndef TERRAIN_H
#define TERRAIN_H

#include <memory>
#include <vector>
#include <map>
#include <QOpenGLShaderProgram>
#include "gameobject.h"
#include "mesh.h"

class Terrain : public GameObject
{
public:
    Terrain(QOpenGLShaderProgram &program);
    Terrain(int size, int nbV, QOpenGLShaderProgram &program);

    void draw(QOpenGLShaderProgram &program, int winter);
    int getSize();
    int getSizeV();
private:
    std::unique_ptr<Mesh> _mesh;
    int sizeV, size;
    const std::map<std::string, std::string> texturesPath{
        {":/heightmap-1.png", "height_map"},
        {":/sand.jpg", "sand"},
        {":/rock.jpg", "rock"},
        {":/snow_rock.jpg", "winter_rock"},
        {":/snow_sand.jpg", "winter_sand"},
    };

    std::vector<Texture> loadTextures();
};

#endif // TERRAIN_H
