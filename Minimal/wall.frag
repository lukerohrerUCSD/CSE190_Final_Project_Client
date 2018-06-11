#version 410 core

in vec2 texCoord;

out vec4 color;

uniform sampler2D caveTex;

void main()
{
	//color = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	color = texture(caveTex, texCoord);
	
}