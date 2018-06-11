#ifndef Transform_H
#define Transform_H

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
#include <list>
#include <vector>
#include "Node.h"

class Transform : public Node {

private:



public:

  Transform(bool isLimb, bool swingDir);
  ~Transform();

  bool isLimb;
  bool swingDir;
  float angle;

  glm::mat4 M;

  std::list<Node*> children;

  void addChild(Node* node);
  void removeChild(Node* node);

  void draw(glm::mat4 C, GLuint shaderProgram);
  void update();

  void march(float rotation_angle);

};

#endif