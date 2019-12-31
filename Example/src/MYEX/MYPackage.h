#pragma once

#include "..\MYENG_DB\Package.h"

class CMyPackage : public mydb::CPackage
{
public:
	CMyPackage();
	virtual ~CMyPackage();

public:
	virtual void CreateModule() override;

};