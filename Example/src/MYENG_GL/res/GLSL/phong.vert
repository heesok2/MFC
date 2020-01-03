#version 330 core

layout (location = 0) in vec3 aVertex;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcel;

struct MyMatrix
{
	mat4 matModel;
	mat4 matView;
	mat4 matProjection;
	mat4 matNormal;
};

uniform MyMatrix myMatrix;

void main()
{
	mat4 matModelViewProjection = myMatrix.matProjection * myMatrix.matView * myMatrix.matModel;
	gl_Position = matModelViewProjection * vec4(aVertex, 1.f);
}