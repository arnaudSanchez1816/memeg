#include "gamecontroller.h"
#include "mainwidget.h"

GameController::GameController()
        : jetRotAngle(0.0f), gameOver(false), points(0), bankingLeft(false), bankingRight(false) {

}

GameController::~GameController() {

}

void GameController::moveTorus(std::shared_ptr<GameObject> &scene) {
    float speed = 30.0 * MainWidget::deltaTime;
    for(auto c = std::begin(torusVector); c != std::end(torusVector); ++c) {
        QVector3D pos = (*c)->getPos();
        (*c)->translate(pos.x(), pos.y(), pos.z() - speed);
        if(pos.z() < -150.0f) {
            c = torusVector.erase(c);
            scene->removeChild(*c);
        }
    }
}
/*
void GameController::checkCollisionTorus(std::shared_ptr<GameObject> &jet, std::shared_ptr<GameObject> &scene) {
    Model *jetM = static_cast<Model*>(jet.get());
    for(auto c = std::begin(torusVector); c != std::end(torusVector); ++c) {
        Model *torus = static_cast<Model*>(c->get());
        if(torus->collide(*jetM)) {
            c = torusVector.erase(c);
            scene->removeChild(*c);
            std::cout << "test" << std::endl;
        }
    }
}
*/
