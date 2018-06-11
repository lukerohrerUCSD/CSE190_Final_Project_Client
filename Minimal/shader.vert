#version 410 core

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

layout(location = 0) in vec3 position;
//layout(location = 1) in vec2 texCoords;
//layout(location = 1) in vec3 normal;

//out vec3 fragVert;
//out vec3 fragNormal;
out vec3 TexCoords;

void main() {

	//fragVert = vec3(model * vec4(position, 1.0f));
	//fragNormal = mat3(transpose(inverse(model))) * normal;
	gl_Position = projection * view * model * vec4(position, 1.0f);
	TexCoords = position;
}