#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "camera.h"
#include <memory>
#include <list>
#include "gameobject.h"

class GameController
{
public:
    Camera activeCamera;
    int points;
    bool gameOver;
    float jetRotAngle;
    bool bankingLeft, bankingRight;
    std::list<std::shared_ptr<GameObject>> torusVector;

    explicit GameController();
    ~GameController();

    void moveTorus(std::shared_ptr<GameObject> &scene);
//    void checkCollisionTorus(std::shared_ptr<GameObject> &jet, std::shared_ptr<GameObject> &scene);
};

#endif // GAMECONTROLLER_H
