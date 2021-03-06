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
		return MYTYPE_NODE;
	}

};