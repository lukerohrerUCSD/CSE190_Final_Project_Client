#version 410 core

layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragVert;

void main()
{
	mat4 MVP = projection * view * model;
    gl_Position = MVP * vec4(position, 1.0);
    fragVert = vec3(model * vec4(position, 1.0f));
}