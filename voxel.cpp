#include "voxel.h"

Voxel::Voxel(float x, float y, float z)
    : _mesh(std::unique_ptr<VMesh>(new VMesh(x, y, z))), _active(true)
{
    /*
    std::vector<Texture> textures;
    Texture texture;
    QOpenGLTexture *tex = new QOpenGLTexture(QImage("./assets/textures/brick.jpg").mirrored());
    tex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    tex->setMagnificationFilter(QOpenGLTexture::NearestMipMapNearest);
    tex->setWrapMode(QOpenGLTexture::Repeat);
    tex->generateMipMaps();
    tex->bind();
    float aniso = 2.0;
    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
    tex->release();
    texture.id = tex->textureId();
    texture.path = "";
    texture.type = Mesh::DIFFUSE_MAP;
    texture.uniformName = "";
    texture.texture = tex;
    textures.push_back(texture);
    _m = std::unique_ptr<Mesh>(new Mesh(_mesh->_vertices, _mesh->_indices, textures, *_program));
    */
}
/*
void Voxel::draw(Renderer &renderer) {
    _program->bind();
    _program->setUniformValue("viewpos", renderer.camPos);
    _program->setUniformValue("mvp_matrix", renderer._projection * renderer._view);
    _program->setUniformValue("dirLight.sunDirection", renderer.light._pos);
    _program->setUniformValue("dirLight.ambient", renderer.light._ambient);
    _program->setUniformValue("dirLight.diffuse", renderer.light._diffuse);
    _program->setUniformValue("dirLight.specular", renderer.light._specular);
    _program->setUniformValue("transform", _transform);
    _program->setUniformValue("normal_mat", _transform.normalMatrix());
    _m->draw(*_program);
    drawChild(renderer);
}
*/
bool Voxel::isActive() {
    return _active;
}

void Voxel::setActive(bool a) {
    _active = a;
}
