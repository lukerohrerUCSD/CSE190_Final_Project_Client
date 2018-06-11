#include "Geometry.h"

using namespace std;

Geometry::Geometry(char* filename) {

  this->filename = filename;
  this->obj = new Model(filename);

}

Geometry::~Geometry() {

}

void Geometry::draw(glm::mat4 C, GLuint shaderProgram) {

  this->M = C;
  this->obj->toWorld = this->M;
  this->obj->draw(shaderProgram);

}

void Geometry::update() {

}