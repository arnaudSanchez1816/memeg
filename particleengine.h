#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <vector>
#include <random>
#include "particle.h"
#include "renderer.h"

#define MAX_PARTICULES 10000

struct ParticleData {
    QVector4D posSize, color;
    ParticleData(QVector4D ps, QVector4D c)
        : posSize(ps)
        , color(c)
    {}
};

class ParticleEngine : QOpenGLFunctions_4_2_Core
{
public:
    ParticleEngine(ParticleType t, QOpenGLShaderProgram &program);
    ~ParticleEngine();

    void drawParticles(const Renderer &renderer, QOpenGLTexture *height = nullptr);
    void updateParticles();
    void generateParticles(int mapSize, float seuilGeneration);
    void generateParticles(QVector3D pos, float maxPerSeconde);
    int findUnusedParticles();
    void setParticleType(ParticleType t);

private:
    QOpenGLShaderProgram &program;
    Particle particleContainer[MAX_PARTICULES];
    QOpenGLBuffer arrayBuffer;
    std::vector<ParticleData> particlesData;
    int lastUsedParticles;
    double lastTime;
    ParticleType type;

    void initParticles();
};

#endif // PARTICLEENGINE_H
