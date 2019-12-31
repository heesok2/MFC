#pragma once

#include "..\MYENG_DB\Package.h"
class CDocBase;
class CMyPackage : public mydb::CPackage
{
public:
	CMyPackage(CDocBase* pDoc);
	virtual ~CMyPackage();

public:
	virtual void CreateModule() override;

};