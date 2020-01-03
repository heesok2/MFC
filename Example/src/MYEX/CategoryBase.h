#pragma once

#include "CategoryDefine.h"

class CCategoryBase
{
public:
	CCategoryBase();
	virtual ~CCategoryBase();

public:
	virtual void SetMenu(CMFCRibbonBar* pRibbonBar) = 0;

};

