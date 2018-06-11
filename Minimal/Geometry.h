#ifndef Geometry_H
#define Geometry_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#include <OpenGL/gl.h> // Remove this line in future projects
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "Node.h"
#include "Model.h"

class Geometry : public Node {

  struct Container {
    glm::vec3 vertex;
    glm::vec3 normal;
  };

private:

  glm::mat4 M;
  const char* filename;
  Model * obj;

public:

  Geometry(char* filename);
  ~Geometry();

  void draw(glm::mat4 C, GLuint shaderProgram);
  void update();

};

#endif