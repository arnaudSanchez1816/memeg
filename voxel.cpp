#include "voxel.h"

Voxel::Voxel()
    :  _active(false), _top(false)
{}

bool Voxel::isActive() {
    return _active;
}

void Voxel::setActive(bool a) {
    _active = a;
}

bool Voxel::isTop() {
    return _top;
}

void Voxel::setTop(bool a) {
    _top = a;
}
