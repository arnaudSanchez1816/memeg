#include "particle.h"
#include <iostream>
#include "mainwidget.h"

Particle::Particle()
    : _position(QVector3D(0.0f, 0.0f, 0.0f))
    , _color(QVector4D(1.0f, 1.0f, 1.0f, 1.0f))
    , _life(-1000.0f)
    , _velocity(QVector3D(0.0f, 0.0f, 0.0f))
    , lastTime(0)
    , _size(5.0f)
{
    _originalSize = _size;
    _originalLife = _life;
}

Particle::Particle(QVector3D pos, QVector4D color, float theta, float phi, float speed, int life, float size)
    : _position(pos)
    , _color(color)
    , _life(life)
    , lastTime(0)
    , _size(size)
{
    float thetaR = qDegreesToRadians(theta);
    float phiR = qDegreesToRadians(phi);
    float x = speed * sin(phiR) * cos(thetaR);
    float z = speed * sin(phiR) * sin(thetaR);
    float y = speed * cos(phiR);
    _velocity = QVector3D(x, y, z);
    _originalSize = _size;
    _originalLife = _life;
}

void Particle::update() {
    _life -= MainWidget::deltaTime;
    if(_life > 0) {
        _position += (_velocity * MainWidget::deltaTime);
        if(_position.y() <= 0.0f) {
            _life = 0;
        }
        float ageRatio = _life / _originalLife;
        if(_size > 2.0f) {
            _size = _originalSize * ageRatio;
        }
       // _color.setW(ageRatio + 0.2f);
    }
}

QVector3D Particle::getPosition() {
    return _position;
}

QVector4D Particle::getPosSize() {
    return QVector4D(_position.x(), _position.y(), _position.z(), _size);
}

QVector4D Particle::getColor() {
    return _color;
}

bool Particle::isAlive() {
    return _life > 0.0f;
}

Particle Particle::generateNewParticle(int mapSize, ParticleType type) {
    switch (type) {
    case ParticleType::Snow:
        return generateSnowParticle(mapSize);
    case ParticleType::Rain:
        return generateRainParticle(mapSize);
    default:
        break;
    }
    return generateSnowParticle(mapSize);
}

Particle Particle::generateSnowParticle(int mapSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disXZ(0.0, (float) mapSize);
    std::uniform_real_distribution<> disY(35.0, 48.0);
    std::uniform_real_distribution<> disSp(8.0, 12.0);
    std::uniform_int_distribution<> disPhi(160, 170);
    std::uniform_real_distribution<> disSi(3.0f, 4.0f);
    return Particle(QVector3D(disXZ(gen), disY(gen), disXZ(gen))
                    , QVector4D(1.0f, 1.0f, 1.0f, 1.0f)
                    , 0.0f
                    , disPhi(gen)
                    , disSp(gen)
                    , 10
                    , disSi(gen));
}

Particle Particle::generateRainParticle(int mapSize) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disXZ(0.0, (float) mapSize);
    std::uniform_real_distribution<> disY(40.0, 55.0);
    std::uniform_real_distribution<> disSp(20.0, 25.0);
    std::uniform_int_distribution<> disPhi(170, 175);
    std::uniform_real_distribution<> disSi(2.0f, 2.0f);
    return Particle(QVector3D(disXZ(gen), disY(gen), disXZ(gen))
                    , QVector4D(0.1f, 0.7f, 0.9f, 1.0f)
                    , 0.0f
                    , disPhi(gen)
                    , disSp(gen)
                    , 4
                    , disSi(gen));
}

Particle Particle::generateBulletParticle(QVector3D pos) {
    return Particle(pos
                    , QVector4D(1.0f, 1.0f, 0.2f, 1.0f)
                    , 90.0f
                    , 90
                    , 100
                    , 1.0f
                    , 2.0f);
}
