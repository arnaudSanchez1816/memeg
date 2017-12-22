#ifndef SKYBOX_H
#define SKYBOX_H

#include <QOpenGLShaderProgram>
#include <vector>
#include "mesh.h"
#include "gameobject.h"

class Skybox : public GameObject
{
public:
    Skybox(QOpenGLShaderProgram &program)
        : _program(program), cubeMap(nullptr), skyboxTexture(nullptr)
    {
        initSkybox();
    }
    void draw(Renderer &renderer);
private:
    Mesh *cubeMap;
    QOpenGLTexture *skyboxTexture;
    QOpenGLShaderProgram &_program;
    const std::vector<std::string> sbFaces { //skybox1
        "assets/skybox/miramar_rt.jpg",
        "assets/skybox/miramar_lf.jpg",
        "assets/skybox/miramar_up.jpg",
        "assets/skybox/miramar_dn.jpg",
        "assets/skybox/miramar_bk.jpg",
        "assets/skybox/miramar_ft.jpg"
    };
    /*
    const std::vector<std::string> sbFaces { //skybox2
        "assets/skybox2/right.jpg",
        "assets/skybox2/left.jpg",
        "assets/skybox2/top.jpg",
        "assets/skybox2/bottom.jpg",
        "assets/skybox2/back.jpg",
        "assets/skybox2/front.jpg"
    };*/
    const std::vector<float> skyboxVertices= {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    void initSkybox();
};

#endif // SKYBOX_H
