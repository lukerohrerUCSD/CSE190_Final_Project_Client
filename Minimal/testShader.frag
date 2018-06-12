#version 410 core

out vec4 fragColor;
in vec2 TexCoords;

uniform sampler2D tex;

void main()
{
	//fragColor = vec4(0.0f, 0.0f, 0.5f, 1.0f);

	fragColor = texture(tex, TexCoords);
}