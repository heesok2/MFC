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

out vec3 aFragPos;
out vec3 aFragNormal;
out vec2 aFragTexcel;

void main()
{
	mat4 matModelView = myMatrix.matView * myMatrix.matModel;
	aFragPos = vec3(matModelView * vec4(aVertex, 1.f));
	aFragNormal = vec3(myMatrix.matNormal * vec4(aNormal, 1.f));
	aFragTexcel = aTexcel;

	mat4 matModelViewProjection = myMatrix.matProjection * myMatrix.matView * myMatrix.matModel;
	gl_Position = matModelViewProjection * vec4(aVertex, 1.f);
}