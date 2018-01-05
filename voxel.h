#ifndef VOXEL_H
#define VOXEL_H

#include "gameobject.h"
#include "mesh.h"
#include "vmesh.h"

enum BlockType {
    BlockType_Default = 0,
    BlockType_Brick,
    BlockType_Dirt
};

class Voxel
{
public:
    std::unique_ptr<VMesh> _mesh;
    Voxel(float x, float y, float z);

    bool isActive();
    void setActive(bool a);
private:
    bool _active;
    BlockType _blockType;
};

#endif // VOXEL_H
