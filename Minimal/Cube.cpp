#include "Cube.h"
#include <iostream>

unsigned char* loadPPM(const char* filename, int& width, int& height)
{
  const int BUFSIZE = 128;
  FILE* fp;
  unsigned int read;
  unsigned char* rawData;
  char buf[3][BUFSIZE];
  char* retval_fgets;
  size_t retval_sscanf;

  if ((fp = fopen(filename, "rb")) == NULL)
  {
    std::cerr << "error reading ppm file, could not locate " << filename << std::endl;
    width = 0;
    height = 0;
    return 0;
  }

  // Read magic number:
  retval_fgets = fgets(buf[0], BUFSIZE, fp);

  // Read width and height:
  do
  {
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
  } while (buf[0][0] == '#');
  retval_sscanf = sscanf(buf[0], "%s %s", buf[1], buf[2]);
  width = atoi(buf[1]);
  height = atoi(buf[2]);

  // Read maxval:
  do
  {
    retval_fgets = fgets(buf[0], BUFSIZE, fp);
  } while (buf[0][0] == '#');

  // Read image data:
  rawData = new unsigned char[width * height * 3];
  read = fread(rawData, width * height * 3, 1, fp);
  fclose(fp);
  if (read != 1)
  {
    std::cerr << "error parsing ppm file, incomplete data" << std::endl;
    delete[] rawData;
    width = 0;
    height = 0;

    return 0;
  }

  return rawData;
}


Cube::Cube() {


  this->toWorld = glm::mat4(1.0f);

  setUpCube();

  setUpFaces();

  setUpSkybox();
}

Cube::~Cube() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void Cube::setUpCube() {

  scaleFactor = 20.0f;
  float CUBESIZE = 0.005f;

  //Set up front side vertices
  //0 - bottom left front
  this->vertices.push_back(glm::vec3(-CUBESIZE, -CUBESIZE, CUBESIZE));
  //1 - bottom right front
  this->vertices.push_back(glm::vec3(CUBESIZE, -CUBESIZE, CUBESIZE));
  //2 - top right front
  this->vertices.push_back(glm::vec3(CUBESIZE, CUBESIZE, CUBESIZE));
  //3 - top left front
  this->vertices.push_back(glm::vec3(-CUBESIZE, CUBESIZE, CUBESIZE));
  //Set up back side vertices
  //4 - bottom left back
  this->vertices.push_back(glm::vec3(-CUBESIZE, -CUBESIZE, -CUBESIZE));
  //5 - bottom right back
  this->vertices.push_back(glm::vec3(CUBESIZE, -CUBESIZE, -CUBESIZE));
  //6 - top right back
  this->vertices.push_back(glm::vec3(CUBESIZE, CUBESIZE, -CUBESIZE));
  //7 - top left back
  this->vertices.push_back(glm::vec3(-CUBESIZE, CUBESIZE, -CUBESIZE));
  

  unsigned int indices_array[] = {
  //front face
    2, 1, 0,
    0, 3, 2,
    //right face
    6, 5, 1,
    1, 2, 6,
    //back face
    5, 6, 7,
    7, 4, 5,
    //left face
    3, 0, 4,
    4, 7, 3,
    //bottom face
    1, 5, 4,
    4, 0, 1,
    //top face
    3, 7, 6,
    6, 2, 3
  };

  for (int i = 35; i >= 0; i--) {
    this->indices.push_back(indices_array[i]);
  }

}

void Cube::setUpFaces() {

  this->faces.push_back("vr_test_pattern.ppm");
  this->faces.push_back("vr_test_pattern.ppm");
  this->faces.push_back("vr_test_pattern.ppm");
  this->faces.push_back("vr_test_pattern.ppm");
  this->faces.push_back("vr_test_pattern.ppm");
  this->faces.push_back("vr_test_pattern.ppm");
}

unsigned int Cube::loadCubeMap(std::vector<const GLchar*> faces) {

  unsigned int textureID;
  glGenTextures(1, &textureID);
  glActiveTexture(GL_TEXTURE0);

  int width, height;
  unsigned char* image;

  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
  for (GLuint i = 0; i < faces.size(); i++)
  {
    image = loadPPM(faces[i], width, height);
    glTexImage2D(
      GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
      GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
    );
  }

  //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  //glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

  return textureID;

}

void Cube::setUpSkybox() {

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

  this->cubeMapTexture = loadCubeMap(faces);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

void Cube::draw(GLuint shaderProgram) {

  glm::mat4 model = glm::scale(this->toWorld, glm::vec3(scaleFactor));

  glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, &model[0][0]);

  glBindVertexArray(VAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTexture);
  glDrawElements(GL_TRIANGLES, (GLsizei)this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glDepthMask(GL_TRUE);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

unsigned int Cube::getSkybox() {
  return this->cubeMapTexture;
}

void Cube::scale(float factor) {
  scaleFactor += factor;
  if (scaleFactor < 1.0f) scaleFactor = 1.0f;
  if (scaleFactor > 50.0f) scaleFactor = 50.0f;
}

void Cube::resetScale() {
  scaleFactor = 1.0f;
}