#ifndef VCHUNK_H
#define VCHUNK_H

#include "gameobject.h"
#include "voxel.h"

class VChunk : public GameObject
{
public:
    static const int CHUNK_SIZE = 16;
    VChunk(QOpenGLShaderProgram *program);
    ~VChunk();

    void update(float dt);
    void draw(Renderer &renderer) override;
    void createMesh();
private:
    Voxel ****_voxels;
    std::unique_ptr<Mesh> _mesh;
    QOpenGLShaderProgram *_program;
    std::vector<Vertex> _vertices;
    std::vector<unsigned int> _indices;
    std::vector<Texture> _texs;

    void addVoxel(const Voxel &voxel, unsigned int cpt);
};

#endif // VCHUNK_H
