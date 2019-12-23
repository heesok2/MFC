#pragma once

#include "Entity.h"

class AFX_EXT_CLASS CEntityNode : public mydb::CEntity
{
public:
	CEntityNode();
	virtual ~CEntityNode();
	
public:
	MYKEY myKey; // Must be defined first.

};
