#include "Transform.h"
#include <iostream>

using namespace std;

Transform::Transform(bool isLimb, bool swingDir) {

  this->M = glm::mat4(1.0f);

  this->isLimb = isLimb;
  this->swingDir = swingDir;
  this->angle = 0.0f;

}

Transform::~Transform() {

}

void Transform::addChild(Node* node) {

  this->children.push_back(node);
  node->parent = this;

}

void Transform::removeChild(Node* node) {

  this->children.remove(node);
  node->parent = NULL;

}

void Transform::draw(glm::mat4 C, GLuint shaderProgram) {

  glm::mat4 M_new = C * (this->M);
  for (list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
    (*it)->draw(M_new, shaderProgram);
  }

}

void Transform::update() {
  for (list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
    (*it)->update();
  }

  if (isLimb) {
    this->march(0.25f);
  }
}

void Transform::march(float rotation_angle) {

  glm::vec3 temp = glm::vec3(this->M[3][0], this->M[3][1], this->M[3][2]);
  this->M = glm::translate(this->M, glm::vec3(0.0f, 0.0f, 1.0f));
  float rot_amt = rotation_angle;
  if (swingDir == false) {
    rot_amt *= -1;
  }
  this->angle += rot_amt;
  if (this->angle > 25.0f || this->angle < -25.0f) {
    swingDir = !swingDir;
  }
  this->M = glm::rotate(this->M, rot_amt / 180.0f * glm::pi<float>(), glm::vec3(1.0f, 0.0f, 0.0f));
  this->M = glm::translate(this->M, glm::vec3(0.0f, 0.0f, -1.0f));

}