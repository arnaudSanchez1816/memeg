#ifndef VCHUNK_H
#define VCHUNK_H

#include "gameobject.h"
#include "voxel.h"
#include "vmesh.h"
#include "vchunkmanager.h"
#include <map>

class VChunk : public GameObject
{
public:
    static const int CHUNK_SIZE = 48;
    VChunk(VChunkManager &manager, QOpenGLShaderProgram *program);
    ~VChunk();

    void update(float dt);
    void draw(Renderer &renderer) override;
    void setupSphere();
    void setupLandscape();
    void setupCube();
private:
    VChunkManager &_manager;
    Voxel ****_voxels; //matrice voxels
    std::unique_ptr<VMesh> _voxelMesh; //mesh d'un voxel référence
    std::unique_ptr<Mesh> _mesh; //mesh du chunk
    QOpenGLShaderProgram *_program;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _texs;
    const std::map<std::string, std::string> texturesPath{
        {"./assets/textures/grass_side.png", "grass_side"},
        {"./assets/textures/grass_top_c.png", "grass_top"},
        {"./assets/textures/dirt.png", "dirt"}
    };

    void addVoxel(float x, float y, float z, unsigned int cpt, bool isTop);
    void createMesh();
    std::vector<Texture> loadTextures();
};

#endif // VCHUNK_H
