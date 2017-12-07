#ifndef VOXEL_H
#define VOXEL_H

#include <QVector3D>
#include <memory>
#include <vector>
#include <iostream>

class Voxel {

    public :
        Voxel(const QVector3D &center, double s)
            : _points(std::make_unique<std::vector<QVector3D>>()), _isVisible(true), lvl(1) {
                // -1 -1 -1
                _points->emplace_back(QVector3D(center._x + (s / 2) * -1,
                                                center._y + (s / 2) * -1,
                                                center._z + (s / 2) * -1));
                // -1 -1 1
                _points->emplace_back(QVector3D(center._x + (s / 2) * -1,
                                                center._y + (s / 2) * -1,
                                                center._z + (s / 2) *  1));
                // -1 1 -1
                _points->emplace_back(QVector3D(center._x + (s / 2) * -1,
                                                center._y + (s / 2) *  1,
                                                center._z + (s / 2) * -1));
                // -1 1 1
                _points->emplace_back(QVector3D(center._x + (s / 2) * -1,
                                                center._y + (s / 2) *  1,
                                                center._z + (s / 2) *  1));
                // 1 1 -1
                _points->emplace_back(QVector3D(center._x + (s / 2) *  1,
                                                center._y + (s / 2) *  1,
                                                center._z + (s / 2) * -1));
                // 1 1 1
                _points->emplace_back(QVector3D(center._x + (s / 2) *  1,
                                                center._y + (s / 2) *  1,
                                                center._z + (s / 2) *  1));
                // 1 -1 -1
                _points->emplace_back(QVector3D(center._x + (s / 2) *  1,
                                                center._y + (s / 2) * -1,
                                                center._z + (s / 2) * -1));
                // 1 -1 1
                _points->emplace_back(QVector3D(center._x + (s / 2) *  1,
                                                center._y + (s / 2) * -1,
                                                center._z + (s / 2) *  1));
                _data.center = center;
                _data.s = s;
        }
        Voxel(){}
        void drawVoxel();
        void subdivide();
        void undivide();
        const std::vector<QVector3D>& getPoints() const;
        void makeSphere(const QVector3D& sphereCenter, double radius, int complexity);
        int isInSphere(const QVector3D& sphereCenter, double radius);
        void makeCylindre(const QVector3D& origin, const QVector3D& axis, double radius, int complexity);
        int isInCylindre(const QVector3D& origin, const QVector3D& axis, double radius);
        void intersectionSphereCylindre(const QVector3D& sphereCenter, double radiusSphere,
                                        const QVector3D& originCylindre, const QVector3D& axisCylindre, double radiusCylindre, int complexity);
        void soustractionSphereCylindre(const QVector3D& sphereCenter, double radiusSphere,
                                        const QVector3D& originCylindre, const QVector3D& axisCylindre, double radiusCylindre, int complexity);
        void unionSphereCylindre(const QVector3D& sphereCenter, double radiusSphere,
                                 const QVector3D& originCylindre, const QVector3D& axisCylindre, double radiusCylindre, int complexity);
        struct Data {
            QVector3D center;
            double s;
            Voxel* parent;
            std::unique_ptr<Voxel> children[2][2][2];
        };
        Data _data;
    private :
        std::unique_ptr<std::vector<QVector3D>> _points;
        bool _isVisible;
        int lvl;
};

inline std::ostream& operator<<(std::ostream& os, const Voxel& obj) {
    os << "Voxel [ ";
    for(auto i = 0; i < 8; ++i) {
        os << obj.getPoints()[i] << '\n';
    }
    os << "]";
    return os;
}

#endif
