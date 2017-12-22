#ifndef SCENE_H
#define SCENE_H

#include "gameobject.h"
#include <vector>

class Scene :public GameObject
{
public:
    Scene() {}

    void draw(Renderer &renderer) override;
};

#endif // SCENE_H
