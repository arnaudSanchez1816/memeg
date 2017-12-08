#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <QOpenGLShaderProgram>
#include <vector>
#include "mesh.h"
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "gameobject.h"

class Model : public GameObject
{
public:
    Model(std::string path, QOpenGLShaderProgram *program)
        : _program(program)
    {
        loadModel(path);
        std::cout << "fin chargement" << std::endl;
    }
    void draw();
private:
    std::vector<std::unique_ptr<Mesh>> _meshes;
    std::vector<QOpenGLTexture*> _loadedTextures;
    std::string _directory;
    QOpenGLShaderProgram *_program;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};

#endif // MODEL_H
