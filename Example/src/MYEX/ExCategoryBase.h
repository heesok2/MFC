#pragma once

#include "ExCategoryDefine.h"

class CExCategoryBase
{
public:
	CExCategoryBase();
	virtual ~CExCategoryBase();

public:
	virtual void SetMenu(CMFCRibbonBar* pRibbonBar) = 0;

};

