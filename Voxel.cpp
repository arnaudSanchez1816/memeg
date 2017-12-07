#include "Voxel.h"
#include "GL/glut.h"
#include <cmath>
#include <iostream>

const std::vector<QVector3D>& Voxel::getPoints() const {
    return *_points;
}

void Voxel::drawVoxel() {
    if(_isVisible) {
        //faces
        glColor3f(1.0/lvl, 0.5/lvl, 0.2);
        glBegin(GL_TRIANGLE_STRIP);
        for(auto j = 0; j < 8; ++j) {
            QVector3D& p = (*_points)[j];
            glVertex3f(p._x, p._y, p._z);
        }
        glVertex3f((*_points)[0]._x, (*_points)[0]._y, (*_points)[0]._z);
        glVertex3f((*_points)[1]._x, (*_points)[1]._y, (*_points)[1]._z);
        glEnd();
        //sommets
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f((*_points)[1]._x, (*_points)[1]._y, (*_points)[1]._z);
        glVertex3f((*_points)[3]._x, (*_points)[3]._y, (*_points)[3]._z);
        glVertex3f((*_points)[7]._x, (*_points)[7]._y, (*_points)[7]._z);
        glVertex3f((*_points)[5]._x, (*_points)[5]._y, (*_points)[5]._z);
        glEnd();
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f((*_points)[2]._x, (*_points)[2]._y, (*_points)[2]._z);
        glVertex3f((*_points)[0]._x, (*_points)[0]._y, (*_points)[0]._z);
        glVertex3f((*_points)[4]._x, (*_points)[4]._y, (*_points)[4]._z);
        glVertex3f((*_points)[6]._x, (*_points)[6]._y, (*_points)[6]._z);
        glEnd();
        glColor3f(1.0, 1.0, 1.0);
    } else  {
        for(auto i = 0; i < 2; ++i) {
            for(auto j = 0; j < 2; ++j) {
                for(auto k = 0; k < 2; ++k) {
                    if(_data.children[i][j][k] != nullptr){
                        _data.children[i][j][k]->drawVoxel();
                    }
                }
            }
        }
    }
}

void Voxel::subdivide() {
    _isVisible = false;
    double nS = _data.s / 2; 
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                QVector3D nCenter(_data.center._x - (i * nS) + nS/2, _data.center._y - (j * nS) + nS/2, _data.center._z - (k * nS) + nS/2);
                auto nVoxel = std::make_unique<Voxel>(nCenter, nS);
                _data.children[i][j][k] = std::move(nVoxel);
                (*(_data.children[i][j][k]))._data.parent = this;
                (*(_data.children[i][j][k])).lvl = lvl + 1;
            }
        }
    }
}

void Voxel::undivide() {
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                if(_data.children[i][j][k] != nullptr) {
                    _data.children[i][j][k]->undivide();
                }
                _data.children[i][j][k] = nullptr;
            }
        }
    }
    _isVisible = true;
}

void Voxel::makeSphere(const QVector3D& sphereCenter, double radius, int complexity) {
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                if(_data.children[i][j][k] != nullptr) {
                    Voxel& v = *_data.children[i][j][k];
                    int r = v.isInSphere(sphereCenter, radius);
                    if(r == 0) {
                        if(complexity > 0) {
                            v.subdivide();
                            v.makeSphere(sphereCenter, radius, complexity - 1);
                        }
                    } else if(r < 0) {
                        _data.children[i][j][k] = nullptr;
                    }
                }
            }
        }
    }
}

int Voxel::isInSphere(const QVector3D& sphereCenter, double radius) {
    double r = 0; 
    int cpt = 0;
    for(auto i = 0; i < 8; ++i) {
        r = (*_points)[i].getDistance(sphereCenter);
        if(r > pow(radius, 2)) {
            ++cpt;
        }
    }
    if(cpt == 0) return 1; // si voxel dans la sphere if(cpt < 8) return 0; // si voxel en partie dans la sphere
    if(cpt < 8) return 0; // si voxel en partie dans la sphere
    return -1; // si hors de la sphere
}

void Voxel::makeCylindre(const QVector3D& origin, const QVector3D& axis, double radius, int complexity) {
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                if(_data.children[i][j][k] != nullptr) {
                    Voxel& v = *_data.children[i][j][k];
                    int r = v.isInCylindre(origin, axis, radius);
                    if(r == 0) {
                        if(complexity > 0) {
                            v.subdivide();
                            v.makeCylindre(origin, axis, radius, complexity - 1);
                        }
                    } else if(r < 0) {
                        _data.children[i][j][k] = nullptr;
                    }
                }
            }
        }
    }
}

int Voxel::isInCylindre(const QVector3D& origin, const QVector3D& axis, double radius) {
    double r = 0; 
    int cpt = 0;
    QVector3D axisC = axis;
    for(auto i = 0; i < 8; ++i) {
        auto& p = (*_points)[i];
        auto pOnAxis = p.projectOnLine(axisC, origin);
        r = p.getDistance(*pOnAxis);
        bool rB = pOnAxis->isBetweenPoints(origin, QVector3D(origin._x + axis._x, origin._y + axis._y, origin._z + axis._z));
        if(r > pow(radius, 2) || !rB) {
            ++cpt;
        }
    }
    if(cpt == 0) return 1; // si voxel dans la sphere
    if(cpt < 8) return 0; // si voxel en partie dans la sphere
    return -1; // si hors de la sphere
}
//marche pas, je trouve pas
void Voxel::intersectionSphereCylindre(const QVector3D& sphereCenter, double radiusSphere,
        const QVector3D& originCylindre, const QVector3D& axisCylindre, double radiusCylindre, int complexity) {
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                if(_data.children[i][j][k] != nullptr) {
                    Voxel& v = *_data.children[i][j][k];
                    int rS = v.isInSphere(sphereCenter, radiusSphere);
                    int rC = v.isInCylindre(originCylindre, axisCylindre, radiusCylindre);
                    if(rS == 0 && rC == 0) {
                        if(complexity > 0) {
                            v.subdivide();
                            v.intersectionSphereCylindre(sphereCenter, radiusSphere, originCylindre, axisCylindre, radiusCylindre, complexity - 1);
                        }
                    } else if(rS < 0 || rC < 0) {
                        _data.children[i][j][k] = nullptr;
                    }
                }
            }
        }
    }
}

void Voxel::soustractionSphereCylindre(const QVector3D& sphereCenter, double radiusSphere,
        const QVector3D& originCylindre, const QVector3D& axisCylindre, double radiusCylindre, int complexity) {
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                if(_data.children[i][j][k] != nullptr) {
                    Voxel& v = *_data.children[i][j][k];
                    int rS = v.isInSphere(sphereCenter, radiusSphere);
                    int rC = v.isInCylindre(originCylindre, axisCylindre, radiusCylindre);
                    if(rS == 0 || rC == 0) {
                        if(complexity > 0) {
                            v.subdivide();
                            v.soustractionSphereCylindre(sphereCenter, radiusSphere, originCylindre, axisCylindre, radiusCylindre, complexity - 1);
                        } else if (rC == 0) {
                            _data.children[i][j][k] = nullptr;
                        }
                    } else if(rS < 0) {
                        _data.children[i][j][k] = nullptr;
                    }
                    if(rC > 0) {
                        _data.children[i][j][k] = nullptr;
                    }
                }
            }
        }
    }
}

void Voxel::unionSphereCylindre(const QVector3D& sphereCenter, double radiusSphere,
    const QVector3D& originCylindre, const QVector3D& axisCylindre, double radiusCylindre, int complexity) {
    for(auto i = 0; i < 2; ++i) {
        for(auto j = 0; j < 2; ++j) {
            for(auto k = 0; k < 2; ++k) {
                if(_data.children[i][j][k] != nullptr) {
                    Voxel& v = *_data.children[i][j][k];
                    int rS = v.isInSphere(sphereCenter, radiusSphere);
                    int rC = v.isInCylindre(originCylindre, axisCylindre, radiusCylindre);
                    if(rC == 0 || rS == 0) {
                        if(complexity > 0) {
                            v.subdivide();
                            v.unionSphereCylindre(sphereCenter, radiusSphere, originCylindre, axisCylindre, radiusCylindre, complexity - 1);
                        }
                    } else if(rC < 0 && rS < 0) {
                        _data.children[i][j][k] = nullptr;
                    }
                }
            }
        }
    }
}
