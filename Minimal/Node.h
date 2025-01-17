#ifndef Node_H
#define Node_H

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

class Node {

private:



public:

  Node * parent;

  Node();
  ~Node();

  virtual void draw(glm::mat4 C, GLuint shaderProgram) = 0;
  virtual void update() = 0;

};

#endif