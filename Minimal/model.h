#pragma once


#include <GL/glew.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class Model
{
public:
  glm::mat4 toWorld;

  Model(char* path);

  void draw(GLuint shader);


private:
  /*  Model Data  */
  vector<Mesh> meshes;
  string directory;
  vector<Texture> textures_loaded;

  /*  Functions   */
  void loadModel(string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene *scene);

  vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

  GLuint uProjection, uModel, uView;
};