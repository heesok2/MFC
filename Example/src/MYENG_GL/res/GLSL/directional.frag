#version 330 core

struct MyLight
{
	vec3 aLightDir;

	vec3 aAmbient;
	vec3 aDiffuse;
	vec3 aSpecular;
};

struct MyMaterial
{
	sampler2D DiffuseTex2D;
	sampler2D SpecularTex2D;
	sampler2D EmissionTex2D;
	float fShininess;
};

uniform MyLight myLight;
uniform MyMaterial myMaterial;

in vec2 aTexCoordinate;
in vec3 aNormalVector;
in vec3 aModelViewPosition;

vec3 GetDirectionalLight()
{
	vec3 aAmbientColor = myLight.aAmbient * texture(myMaterial.DiffuseTex2D, aTexCoordinate).rgb;

	vec3 aNormal = normalize(aNormalVector);
	vec3 aLightDir = normalize(-myLight.aLightDir);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = myLight.aDiffuse * fDiffuse * texture(myMaterial.DiffuseTex2D, aTexCoordinate).rgb;

	vec3 aViewDir = normalize(-aModelViewPosition);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), myMaterial.fShininess);
	vec3 aSpecularColor = myLight.aSpecular * fSpecular * texture(myMaterial.SpecularTex2D, aTexCoordinate).rgb;

	return (aAmbientColor + aDiffuseColor + aSpecularColor);
}