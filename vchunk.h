#ifndef VCHUNK_H
#define VCHUNK_H

#include "gameobject.h"
#include "voxel.h"
#include "vchunkmanager.h"

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
    Voxel ****_voxels;
    std::unique_ptr<Mesh> _mesh;
    QOpenGLShaderProgram *_program;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _texs;

    void addVoxel(const Voxel &voxel, unsigned int cpt);
    void createMesh();
};

#endif // VCHUNK_H
