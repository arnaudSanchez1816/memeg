#include "skybox.h"
#include <iostream>

void Skybox::initSkybox() {
    skyboxTexture = new QOpenGLTexture(QOpenGLTexture::TargetCubeMap);
    skyboxTexture->create();
    for (unsigned int i = 0; i < sbFaces.size(); i++) {
        QImage img = QImage(sbFaces[i].c_str()).convertToFormat(QImage::Format_RGBA8888);
        unsigned char *data = img.bits();
        if(i == 0) { //finir init la texture
            skyboxTexture->setSize(img.width(), img.height(), img.depth());
            skyboxTexture->setFormat(QOpenGLTexture::RGBA8_UNorm);
            skyboxTexture->allocateStorage();
        }
        if (data) {
            QOpenGLTexture::CubeMapFace cbf = (QOpenGLTexture::CubeMapFace) (GL_TEXTURE_CUBE_MAP_POSITIVE_X + i);
            skyboxTexture->setData(0, 0, cbf, QOpenGLTexture::RGBA, QOpenGLTexture::UInt8, (const void*)data, 0);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << sbFaces[i] << std::endl;
        }
    }
    skyboxTexture->setWrapMode(QOpenGLTexture::ClampToEdge);
    skyboxTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    skyboxTexture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    skyboxTexture->generateMipMaps();

    std::vector<Vertex> sbVertices;
    std::vector<Texture> textures;
    Texture texture;
    texture.id = 0;
    texture.path = "";
    texture.type = Mesh::DIFFUSE_MAP;
    texture.uniformName = "skybox";
    texture.texture = skyboxTexture;
    textures.push_back(texture);
    for(int i = 0; i < skyboxVertices.size(); i+=3) {
        Vertex v;
        v._position = QVector3D(skyboxVertices[i], skyboxVertices[i + 1], skyboxVertices[i + 2]);
        sbVertices.push_back(v);
    }
    cubeMap = new Mesh(sbVertices, std::vector<unsigned int>(), textures, _program);
}

void Skybox::draw(Renderer &renderer) {
    glDepthFunc(GL_LEQUAL);
    _program.bind();
    skyboxTexture->bind(0);
    QMatrix4x4 view = renderer._view;
    view.setColumn(3, QVector4D(0.0,0.0,0.0,1.0));
    _program.setUniformValue("mvp_matrix", renderer._projection * view);
    _program.setUniformValue("skybox", 0);
    cubeMap->draw(_program);
    skyboxTexture->release();
    glDepthFunc(GL_LESS);
}
