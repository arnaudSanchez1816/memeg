#include "vchunkmanager.h"
#include <iostream>

VChunkManager::VChunkManager()
{
}

int VChunkManager::getNoiseValue(float x, float z) {
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
    int OldRange = (1.0 - -1.0);
    int NewRange = (47 - 0);
    double valN = finalTerrain.GetValue(x / 64.0f, 0.0, z / 64.0f);
    float val = std::max(std::min(valN, 1.0), -1.0);
    int NewValue = (((val - -1.0) * NewRange) / OldRange);

    return NewValue;
}
