#include "vchunk.h"
#include <algorithm>

const int VChunk::CHUNK_SIZE;

VChunk::VChunk(VChunkManager &manager, QOpenGLShaderProgram *program)
    : _program(program), _manager(manager), _voxelMesh(std::unique_ptr<VMesh>(new VMesh(0.0f, 0.0f, 0.0f)))
{
    // Create the blocks
    _voxels = new Voxel***[CHUNK_SIZE];
    for(int i = 0; i < CHUNK_SIZE; i++) {
        _voxels[i] = new Voxel**[CHUNK_SIZE];
        for(int j = 0; j < CHUNK_SIZE; j++) {
            _voxels[i][j] = new Voxel*[CHUNK_SIZE];
            for(int k = 0; k < CHUNK_SIZE; ++k) {
                _voxels[i][j][k] = new Voxel();
            }
        }
    }
    _texs = loadTextures();
}

VChunk::~VChunk() {
    // Delete the blocks
    for (int i = 0; i < CHUNK_SIZE; ++i) {
        for (int j = 0; j < CHUNK_SIZE; ++j) {
            for(int k = 0; k < CHUNK_SIZE; ++k) {
                delete _voxels[i][j][k];
            }
            delete [] _voxels[i][j];
        }
        delete [] _voxels[i];
    }
    delete [] _voxels;
}

void VChunk::draw(Renderer &renderer) {
    _program->bind();
    _program->setUniformValue("viewpos", renderer.camPos);
    _program->setUniformValue("mvp_matrix", renderer._projection * renderer._view);
    _program->setUniformValue("dirLight.sunDirection", renderer.light._pos);
    _program->setUniformValue("dirLight.ambient", renderer.light._ambient);
    _program->setUniformValue("dirLight.diffuse", renderer.light._diffuse);
    _program->setUniformValue("dirLight.specular", renderer.light._specular);
    _program->setUniformValue("transform", _transform);
    _program->setUniformValue("normal_mat", _transform.normalMatrix());
    _mesh->draw(*_program);
    drawChild(renderer);
}


void VChunk::createMesh() {
    unsigned int cpt = 0;
    _vertices.clear();
    _indices.clear();
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                if(_voxels[x][y][z]->isActive()) {
                    addVoxel(x, y, z, cpt, _voxels[x][y][z]->isTop());
                    cpt += _voxelMesh->_vertices.size();
                }
            }
        }
    }
    _mesh = std::unique_ptr<Mesh>(new Mesh(_vertices, _indices, _texs, *_program));
}

void VChunk::addVoxel(float x, float y, float z, unsigned int cpt, bool isTop) {
    // add vertices of voxel to chunk mesh
    std::transform(_voxelMesh->_vertices.begin(), _voxelMesh->_vertices.end(),std::back_inserter(_vertices), [x, y, z, isTop] (const Vertex &v) {
        Vertex vertex;
        vertex._normal = v._normal;
        vertex._tangent = v._tangent;
        vertex._texCoords = v._texCoords;
        vertex._isTop = isTop;
        QVector3D pos = v._position;
        pos.setX(pos.x() + x);
        pos.setY(pos.y() + y);
        pos.setZ(pos.z() + z);
        vertex._position = pos;

        return vertex;
    });
    //add indices
    std::transform(_voxelMesh->_indices.begin(), _voxelMesh->_indices.end(),std::back_inserter(_indices), [cpt] (unsigned int i) { return i + cpt; });
}

void VChunk::setupCube() {
    for (int z = 0; z < CHUNK_SIZE; z++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                 _voxels[x][y][z]->setActive(true);
            }
        }
    }
    createMesh();
}

void VChunk::setupSphere() {
    for (int z = 0; z < CHUNK_SIZE; z++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int x = 0; x < CHUNK_SIZE; x++) {
                if (sqrt((float) (x-CHUNK_SIZE/2.0f)*(x-CHUNK_SIZE/2.0f) + (y-CHUNK_SIZE/2.0f)*(y-CHUNK_SIZE/2.0f) + (z-CHUNK_SIZE/2.0f)*(z-CHUNK_SIZE/2.0f)) < CHUNK_SIZE/2.0f) {
                    _voxels[x][y][z]->setActive(true);
                }
            }
        }
    }
    createMesh();
}

void VChunk::setupLandscape() {
    for(int x = 0; x < CHUNK_SIZE; x++) {
        for(int z = 0; z < CHUNK_SIZE; z++) {
            // Use the noise library to get the height value of x, z
            int height = _manager.getNoiseValue(x + getPos().x(), z + getPos().z());
            height = std::max(height, 1);
            for (int y = 0; y < height; y++) {
                _voxels[x][y][z]->setActive(true);
                _voxels[x][y][z]->setTop(y == (height - 1));
            }
        }
    }
    createMesh();
}

std::vector<Texture> VChunk::loadTextures() {
    std::vector<Texture> textures;
    //int cptId = 1;
    for(auto it = texturesPath.begin(); it != texturesPath.end(); ++it) {
        Texture texture;
        QOpenGLTexture *tex = new QOpenGLTexture(QImage(it->first.c_str()).mirrored());
        tex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        tex->setMagnificationFilter(QOpenGLTexture::NearestMipMapNearest);
        tex->setWrapMode(QOpenGLTexture::Repeat);
        tex->generateMipMaps();
        tex->bind();
        float aniso = 2.0;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
        tex->release();
        //texture.id = cptId++;
        texture.id = tex->textureId();
        texture.path = it->first;
        texture.type = Mesh::DIFFUSE_MAP;
        texture.uniformName = it->second;
        texture.texture = tex;
        textures.push_back(texture);
    }
    return textures;
}
