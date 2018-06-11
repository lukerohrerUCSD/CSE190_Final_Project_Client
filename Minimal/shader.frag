#version 410 core

//in vec3 fragVert;
//in vec3 fragNormal;
in vec3 TexCoords;

out vec4 fragColor;

uniform samplerCube skybox;


void main(void) {

	fragColor = texture(skybox, TexCoords);

}