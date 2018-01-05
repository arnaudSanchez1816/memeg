#ifndef VOXEL_H
#define VOXEL_H

enum BlockType {
    BlockType_Default = 0,
    BlockType_Brick,
    BlockType_Dirt
};

class Voxel
{
public:
    Voxel();

    bool isActive();
    void setActive(bool a);
    bool isTop();
    void setTop(bool a);
private:
    bool _active, _top;
    BlockType _blockType;
};

#endif // VOXEL_H
