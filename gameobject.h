#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QVector3D>
#include <QMatrix4x4>
#include <memory>
#include <list>
#include "renderer.h"

class GameObject : public std::enable_shared_from_this<GameObject>
{
public:
    QMatrix4x4 _transform;

    GameObject()
        : _transform(), _parent(), _children(),
          _x(0.0f), _y(0.0f), _z(0.0f),
          _rotX(0.0f), _rotY(0.0f), _rotZ(0.0f),
          _sX(1.0f), _sY(1.0f), _sZ(1.0f)
    {}

    void translate(float x, float y = 0.0f, float z = 0.0f);
    void setScale(float x, float y, float z);
    void rotateX(float val);
    void rotateY(float val);
    void rotateZ(float val);

    QVector3D getPos(bool relative = false);
    QVector3D getFront();
    QVector3D getUp();
    QVector3D getRight();

    void addChild(std::shared_ptr<GameObject> child);
    void removeChild(std::shared_ptr<GameObject> child);
    std::shared_ptr<GameObject> getPtr();
    virtual void draw(Renderer &renderer);

    std::list<std::shared_ptr<GameObject>>& getChildren();

protected:
    float _x, _y, _z;
    float _rotX, _rotY, _rotZ;
    float _sX, _sY, _sZ;

    void drawChild(Renderer &renderer);

private:
    std::weak_ptr<GameObject> _parent;
    std::list<std::shared_ptr<GameObject>> _children;

    /**
     * @brief updateLocalTransform
     * update this object transform matrix only
     */
    QMatrix4x4 updateLocalTransform();
    /**
     * @brief updateAllTransform
     * update this and all children transform matrix
     */
    void updateAllTransform();

    void setParent(std::shared_ptr<GameObject> parent);
};

#endif // GAMEOBJECT_H
