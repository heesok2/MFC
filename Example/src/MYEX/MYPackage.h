#pragma once

#include "..\MYEX_DB\Package.h"

class CMYPackage : public CPackage
{
public:
	CMYPackage();
	virtual ~CMYPackage();

public:
	virtual void CreateModule() override;

};