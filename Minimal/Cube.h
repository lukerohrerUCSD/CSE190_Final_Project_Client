#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Cube {
private:
  std::vector<glm::vec3> vertices;
  std::vector<unsigned int> indices;
  std::vector<const GLchar*> faces;

  unsigned int cubeMapTexture;

  void setUpCube();
  void setUpFaces();
  void setUpSkybox();

  unsigned int loadCubeMap(std::vector<const GLchar*> faces);

public:

  Cube();
  ~Cube();

  glm::mat4 toWorld;
  float scaleFactor;

  void draw(GLuint shaderProgram);
  unsigned int getSkybox();
  void scale(float factor);
  void resetScale();

  GLuint VAO, VBO, EBO;
};