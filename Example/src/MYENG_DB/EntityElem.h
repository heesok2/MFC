#pragma once

#include "Entity.h"
#include "ElementType.h"

class AFX_EXT_CLASS CEntityElem : public mydb::CEntity
{
public:
	CEntityElem();
	virtual ~CEntityElem();
	
public:
	MYKEY Key; // Must be defined first.

	UINT uiType;
	std::vector<MYITR> aItrNode;
};