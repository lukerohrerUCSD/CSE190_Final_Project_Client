#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/types.h>
#include <assimp/scene.h>

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
using namespace std;

struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  GLuint id;
  string type;
  aiString path;
};

struct Material {
  glm::vec3 ambient;
  glm::vec3 diffuse;
  glm::vec3 specular;
  float shininess;
};

class Mesh {
public:

  Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;

  void draw(GLuint shaderProgram);
  void center();

private:

  GLuint VAO, VBO, EBO;

  void setUpMesh();

};