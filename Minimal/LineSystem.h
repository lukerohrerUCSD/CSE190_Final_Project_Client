#pragma once

#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class LineSystem {

public:

  GLuint VAO, VBO, EBO;
  glm::mat4 toWorld;

  glm::vec3 position;
  glm::mat4 quat;

  std::vector<glm::vec3> vertices;

  glm::vec3 colorVal;

  LineSystem();
  void draw(GLuint shaderProgram, glm::vec3 pointA, glm::vec3 pointB);

};
