#pragma once

#include "Entity.h"

class AFX_EXT_CLASS CEntityMesh : public mydb::CEntity
{
public:
	CEntityMesh();
	virtual ~CEntityMesh();
	
public:
	MYKEY Key; // Must be defined first.

	std::vector<MYITR> aItrMesh;
	std::vector<MYITR> aItrNode;
	std::vector<MYITR> aItrElement;
	std::vector<MYITR> aItrTexture;

};