#include "pch.h"
#include "EntityNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CEntityNode::CEntityNode()
{
	Key = 0;
	aVertex = glm::vec3(0.f);
	aNormal = glm::vec3(0.f);
	aTexCord = glm::vec3(0.f);
	aTangent = glm::vec3(0.f);
	aBitangent = glm::vec3(0.f);
}

CEntityNode::~CEntityNode()
{
}