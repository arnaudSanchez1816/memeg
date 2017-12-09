#include "model.h"
#include <iostream>
#include <utility>

unsigned int cptId = 0;

void Model::draw() {
    for(int i = 0; i < _meshes.size() ; ++i) {
        _program->setUniformValue("transform", _transform);
        _program->setUniformValue("normal_mat", _transform.normalMatrix());
        _meshes[i]->draw(*_program);
    }
}

void Model::loadModel(std::string path) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    //get all node's meshes
    for(unsigned int i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(std::move(processMesh(mesh, scene)));
    }
    for(unsigned int i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene);
    }
}

std::unique_ptr<Mesh> Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mesh->mNumVertices; ++i) {
        Vertex vertex;
        //position
        QVector3D vector;
        vector.setX(mesh->mVertices[i].x);
        vector.setY(mesh->mVertices[i].y);
        vector.setZ(mesh->mVertices[i].z);
        vertex._position = vector;
        //normals
        if(mesh->mNormals) {
            vector.setX(mesh->mNormals[i].x);
            vector.setY(mesh->mNormals[i].y);
            vector.setZ(mesh->mNormals[i].z);
            vertex._normal = vector;
        }
        //tex coord
        if(mesh->mTextureCoords[0]) { // si ya des tex coords
            QVector2D vec;
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex._texCoords = vec;
        } else {
            vertex._texCoords = QVector2D(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }
    for(unsigned int i = 0; i < mesh->mNumFaces; ++i) { //indices
        aiFace &face = mesh->mFaces[i];
        for(auto j = 0u; j < face.mNumIndices; ++j) {
            indices.push_back(face.mIndices[j]);
        }
    }
    if(mesh->mMaterialIndex >= 0) { //si ya des materials
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, Mesh::DIFFUSE_MAP);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, Mesh::SPECULAR_MAP);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    return std::unique_ptr<Mesh>(new Mesh(vertices, indices, textures, *_program));
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); ++i) {
        aiString str;
        mat->GetTexture(type, i, &str);
        Texture texture;
        std::string p = _directory + "/tex/";
        p += str.C_Str();
        QOpenGLTexture *tex = new QOpenGLTexture(QImage(p.c_str()));
        tex->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
        tex->setMagnificationFilter(QOpenGLTexture::Linear);
        tex->setWrapMode(QOpenGLTexture::Repeat);
        _loadedTextures.push_back(tex);
        texture.id = cptId++;
        texture.path = str;
        texture.uniformName = "";
        texture.type = typeName;
        texture.texture = tex;
        textures.push_back(texture);
    }
    return textures;
}
