#pragma once

#include "Entity.h"

class AFX_EXT_CLASS CEntityNode : public mydb::CEntity
{
public:
	CEntityNode();
	virtual ~CEntityNode();
	
public:
	MYKEY Key; // Must be defined first.
	
	glm::vec3 aVertex;
	glm::vec3 aNormal;
	glm::vec2 aTexCord;
	glm::vec3 aTangent;
	glm::vec3 aBitangent;

};
