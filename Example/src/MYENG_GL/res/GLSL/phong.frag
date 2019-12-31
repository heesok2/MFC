#version 330 core

out vec4 FragColor;

vec3 GetDirectionalLight();

void main()
{
	vec3 aColor = GetDirectionalLight();
	FragColor = vec4(aColor, 1.f);
}