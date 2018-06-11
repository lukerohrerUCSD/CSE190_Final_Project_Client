#version 410 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main()
{
	mat4 MVP = projection * view * model;
    gl_Position = MVP * vec4(position, 1.0);
    texCoord = texCoords;
}