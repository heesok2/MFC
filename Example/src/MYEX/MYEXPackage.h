#pragma once

#include "..\MYEX_DB\Package.h"

class CMYEXPackage : public mydb::CPackage
{
public:
	CMYEXPackage();
	virtual ~CMYEXPackage();

public:
	virtual void CreateModule() override;

};