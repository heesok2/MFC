#version 330 core

layout (location = 0) in vec2 aVertex;
layout (location = 1) in vec2 aTexcel;

out vec2 aTexCoordinate;

void main()
{
	aTexCoordinate = aTexcel;
	gl_Position = vec4(aVertex.x, aVertex.y, 0.f, 1.f);
}