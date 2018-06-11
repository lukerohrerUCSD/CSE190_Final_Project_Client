#version 410 core

in vec3 fragVert;

out vec4 color;

uniform vec3 colorVal;

void main()
{
	//color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	color = vec4(colorVal, 1.0f);
	
}