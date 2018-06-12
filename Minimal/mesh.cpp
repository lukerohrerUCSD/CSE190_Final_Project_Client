#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  this->center();
  this->setUpMesh();

}

void Mesh::center() {
	float xmin = vertices[0].Position.x;
	float xmax = vertices[0].Position.x;
	float ymin = vertices[0].Position.y;
	float ymax = vertices[0].Position.y;
	float zmin = vertices[0].Position.z;
	float zmax = vertices[0].Position.z;

	//Find min and max values.
	for (int i = 1; i < vertices.size(); ++i) {
		if (vertices[i].Position.x < xmin) {
			xmin = vertices[i].Position.x;
		}
		if (vertices[i].Position.x > xmax) {
			xmax = vertices[i].Position.x;
		}
		if (vertices[i].Position.y < ymin) {
			ymin = vertices[i].Position.y;
		}
		if (vertices[i].Position.y > ymax) {
			ymax = vertices[i].Position.y;
		}
		if (vertices[i].Position.z < zmin) {
			zmin = vertices[i].Position.z;
		}
		if (vertices[i].Position.z > zmax) {
			zmax = vertices[i].Position.z;
		}
	}

	//Find middle values
	float x_middle = (xmin + xmax) / 2;
	xmin -= x_middle;
	xmax -= x_middle;
	float y_middle = (ymin + ymax) / 2;
	ymin -= y_middle;
	ymax -= y_middle;
	float z_middle = (zmin + zmax) / 2;
	zmin -= z_middle;
	zmax -= z_middle;

	for (unsigned int i = 0; i < vertices.size(); ++i) {
		vertices[i].Position.x -= x_middle;
		vertices[i].Position.y -= y_middle;
		vertices[i].Position.z -= z_middle;
	}

	//Scale to 2x2x2 box
	float currScale = std::max((zmax - zmin), std::max((ymax - ymin), (xmax - xmin)));
	currScale = 2 / currScale;
	//this->scale(currScale);
	for (unsigned int i = 0; i < vertices.size(); ++i) {
		vertices[i].Position.x *= currScale;
		vertices[i].Position.y *= currScale;
		vertices[i].Position.z *= currScale;
	}


	//current_Offset = glm::vec3(0.0f, 0.0f, 0.0f);
	//scaleSize = 1.0f;
}

void Mesh::draw(GLuint shaderProgram) {

  GLuint diffuseNr = 1;
  GLuint specularNr = 1;

  for (GLuint i = 0; i < this->textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
                                      // Retrieve texture number (the N in diffuse_textureN)
    stringstream ss;
    string number;
    string name = this->textures[i].type;
    if (name == "texture_diffuse")
      ss << diffuseNr++; // Transfer GLuint to stream
    else if (name == "texture_specular")
      ss << specularNr++; // Transfer GLuint to stream
    number = ss.str();
    // Now set the sampler to the correct texture unit
    glUniform1i(glGetUniformLocation(shaderProgram, (name + number).c_str()), i);
    // And finally bind the texture
    glBindTexture(GL_TEXTURE_2D, this->textures[i].id);

	//cout << "TEXTURE LOOP" << endl;

  }

  // Draw mesh
  glBindVertexArray(this->VAO);
  glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  for (GLuint i = 0; i < this->textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}

void Mesh::setUpMesh() {
  // Create buffers/arrays
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->EBO);

  glBindVertexArray(this->VAO);
  // Load data into vertex buffers
  glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
  // A great thing about structs is that their memory layout is sequential for all its items.
  // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
  // again translates to 3/2 floats which translates to a byte array.
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

  // Set the vertex attribute pointers
  // Vertex Positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
  // Vertex Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
  // Texture coordinates
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));

  glBindVertexArray(0);
}