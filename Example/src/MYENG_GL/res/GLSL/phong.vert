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

out vec2 aTexCoordinate;
out vec3 aNormalVector;
out vec3 aModelViewPosition;

void main()
{
	aTexCoordinate = aTexcel;
	aNormalVector = vec3(myMatrix.matNormal * vec4(aNormal, 1.f));
	mat4 matModelView = myMatrix.matModel * myMatrix.matView;
	aModelViewPosition = vec3(matModelView * vec4(aVertex, 1.f));
	
	mat4 matModelViewProjection = myMatrix.matModel * myMatrix.matView * myMatrix.matProjection;
	gl_Position = matModelViewProjection * vec4(aVertex, 1.f);
}