#pragma once

#include "ModuleBase.hpp"
#include "EntityDefine.h"
#include "EntityNode.h"

class AFX_EXT_CLASS CModuleNode : public mydb::CModuleData<CEntityNode>
{
public:
	CModuleNode(mydb::CPackage* pPackage);
	virtual ~CModuleNode();

public:
	virtual MYTYPE GetType() 
	{
		return MYTYP_NODE;
	}

public:
	MYKEY Key; // 
	glm::vec3 aVertex;
	glm::vec3 aNormal;
	glm::vec3 aTexCord;
	glm::vec3 aTangent;
	glm::vec3 aBitangent;

};