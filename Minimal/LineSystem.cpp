#include "LineSystem.h"

LineSystem::LineSystem() {

  colorVal = glm::vec3(0.0f, 1.0f, 0.0f);

  toWorld = glm::mat4(1.0f);

  vertices.clear();

  vertices.push_back(glm::vec3(1000.0f, 0.0f, 10.0f));
  vertices.push_back(glm::vec3(-1000.0f, 0.0f, -100.0f));

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

}

void LineSystem::draw(GLuint shaderProgram, glm::vec3 pointA, glm::vec3 pointB) {

  vertices.clear();

  vertices.push_back(pointA);
  vertices.push_back(pointB);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices.front());
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  toWorld = glm::mat4(1.0f);
  glLineWidth(4.0f);

  GLuint MatrixID = glGetUniformLocation(shaderProgram, "model");
  glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &toWorld[0][0]);

  GLuint colorID = glGetUniformLocation(shaderProgram, "colorVal");
  glUniform3f(colorID, 0.0f, 1.0f, 0.0f);

  glBindVertexArray(VAO);
  glDrawArrays(GL_LINES, 0, 2);
  glBindVertexArray(0);

}