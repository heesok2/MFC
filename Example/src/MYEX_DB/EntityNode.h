#pragma once

#include "Entity.h"

class CEntityNode : public mydb::CEntity
{
public:
	CEntityNode();
	virtual ~CEntityNode();

public:
	virtual const MYKEY GetKey() const override;

public:
	MYKEY myKey; // Must be defined first.

};
