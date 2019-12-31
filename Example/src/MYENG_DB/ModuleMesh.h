#pragma once

#include "ModuleBase.hpp"
#include "EntityDefine.h"
#include "EntityMesh.h"

class AFX_EXT_CLASS CModuleMesh : public mydb::CModuleData<CEntityMesh>
{
public:
	CModuleMesh(mydb::CPackage* pPackage);
	virtual ~CModuleMesh();

public:
	virtual MYTYPE GetType()
	{
		return MYTYPE_MESH;
	}

};