#ifndef VCHUNKMANAGER_H
#define VCHUNKMANAGER_H

#include <noise/noise.h>

using namespace noise;

class VChunkManager
{
public:
    VChunkManager();

    int getNoiseValue(float x, float z);
private:
    float startX, startY, startZ;

};

#endif // VCHUNKMANAGER_H
