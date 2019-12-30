#version 330 core

in vec2 aTexCoordinate;

uniform sampler2D SceneTex2D;

out vec4 FragColor;

void main()
{
	FragColor = vec4(texture(SceneTex2D, aTexCoordinate).rgb, 1.f);
}