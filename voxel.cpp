#include "voxel.h"

Voxel::Voxel(float x, float y, float z)
    : _mesh(std::unique_ptr<VMesh>(new VMesh(x, y, z))), _active(false)
{}

bool Voxel::isActive() {
    return _active;
}

void Voxel::setActive(bool a) {
    _active = a;
}
