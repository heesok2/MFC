#pragma once

#include "ModuleBase.hpp"
#include "EntityDefine.h"
#include "EntityElem.h"

class AFX_EXT_CLASS CModuleElem : public mydb::CModuleData<CEntityElem>
{
public:
	CModuleElem(mydb::CPackage* pPackage);
	virtual ~CModuleElem();

public:
	virtual MYTYPE GetType()
	{
		return MYTYPE_ELEM;
	}

};

