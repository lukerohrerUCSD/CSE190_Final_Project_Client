#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Skybox {
private:
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
  std::vector<const GLchar*> faces;

  unsigned int cubeMapTexture;

  void setUpCube();
  void setUpFaces(bool left);
  void setUpSkybox();

  bool left;

  unsigned int loadCubeMap(std::vector<const GLchar*> faces);

public:

  Skybox();
  Skybox(bool left);
  ~Skybox();

  glm::mat4 toWorld;

  void draw(GLuint shaderProgram);
  unsigned int getSkybox();

  GLuint VAO, VBO, EBO;
};