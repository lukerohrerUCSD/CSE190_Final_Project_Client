#include "Pyramid.h"
#include <iostream>


Pyramid::Pyramid() {


  this->toWorld = glm::mat4(1.0f);

  setUpPyramid();

  setUpFaces();

  setUpSkybox();
}

Pyramid::~Pyramid() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Pyramid::setUpPyramid() {

  scaleFactor = 20.0f;
  float PyramidSIZE = 0.005f * 0.75f;

  //0 - back left bottom
  this->vertices.push_back(glm::vec3(-PyramidSIZE, -PyramidSIZE, PyramidSIZE));
  //1 - back right bottom
  this->vertices.push_back(glm::vec3(PyramidSIZE, -PyramidSIZE, PyramidSIZE));
  //2 - back left top
  this->vertices.push_back(glm::vec3(-PyramidSIZE, PyramidSIZE, PyramidSIZE));
  //3 - back right top
  this->vertices.push_back(glm::vec3(PyramidSIZE, PyramidSIZE, PyramidSIZE));
  //4 - front
  this->vertices.push_back(glm::vec3(0.0f, 0.0f, -PyramidSIZE * 1.33f));
  

  unsigned int indices_array[] = {
  //front face
    2, 0, 1,
    2, 1, 3,
    //right face
    4, 0, 2,
    4, 2, 3,
    //back face
    4, 1, 0,
    4, 3, 1
  };

  for (int i = 17; i >= 0; i--) {
    this->indices.push_back(indices_array[i]);
  }

}

void Pyramid::setUpFaces() {
  /*
  this->faces.push_back("D:\\Stephen\\Documents\\CSE190\\vr_test_pattern.ppm");
  this->faces.push_back("D:\\Stephen\\Documents\\CSE190\\vr_test_pattern.ppm");
  this->faces.push_back("D:\\Stephen\\Documents\\CSE190\\vr_test_pattern.ppm");
  this->faces.push_back("D:\\Stephen\\Documents\\CSE190\\vr_test_pattern.ppm");
  this->faces.push_back("D:\\Stephen\\Documents\\CSE190\\vr_test_pattern.ppm");
  this->faces.push_back("D:\\Stephen\\Documents\\CSE190\\vr_test_pattern.ppm");
  */
}

void Pyramid::setUpSkybox() {

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * 3 * sizeof(GLfloat), &this->vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(int), &this->indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  //this->PyramidMapTexture = loadPyramidMap(faces);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void Pyramid::draw(GLuint shaderProgram) {

  glm::mat4 model = glm::scale(this->toWorld, glm::vec3(scaleFactor));

  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

  glBindVertexArray(VAO);
  //glActiveTexture(GL_TEXTURE0);
  //glBindTexture(GL_TEXTURE_Pyramid_MAP, PyramidMapTexture);
  glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glDepthMask(GL_TRUE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

unsigned int Pyramid::getSkybox() {
  return this->cubeMapTexture;
}

void Pyramid::scale(float factor) {
  scaleFactor += factor;
  if (scaleFactor < 1.0f) scaleFactor = 1.0f;
  if (scaleFactor > 50.0f) scaleFactor = 50.0f;
}

void Pyramid::resetScale() {
  scaleFactor = 1.0f;
}