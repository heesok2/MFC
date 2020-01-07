#version 330 core

struct MyLight
{
	vec3 aPosition;
	vec3 aAmbient;
	vec3 aDiffuse;
	vec3 aSpecular;
};

struct MyMaterial
{	
	float fShininess;
};

uniform MyLight myLight;
uniform MyMaterial myMaterial;

in vec3 aFragPos;
in vec3 aFragNormal;
in vec2 aFragTexcel;

out vec4 aFragColor;

vec3 GetPointLigth()
{
	vec3 aAmbientColor = myLight.aAmbient;// * texture(myMaterial.aDiffuse, aFragTexcel).rgb;

	vec3 aNormal = normalize(aFragNormal);
	vec3 aLightDir = normalize(myLight.aPosition - aFragPos);
	float fDiffuse = max(dot(aNormal, aLightDir), 0.f);
	vec3 aDiffuseColor = myLight.aDiffuse * fDiffuse;// * texture(myMaterial.aDiffuse, aFragTexcel).rgb;

	vec3 aViewDir = normalize(-aFragPos);
	vec3 aReflectDir = reflect(-aLightDir, aNormal);
	float fSpecular = pow(max(dot(aViewDir, aReflectDir), 0.f), myMaterial.fShininess);
	vec3 aSpecularColor = myLight.aSpecular * fSpecular;

	return (aAmbientColor + aDiffuseColor + aSpecularColor);
}

void main()
{
	vec3 aColor = GetPointLigth();
	aFragColor = vec4(aColor, 1.f);
}