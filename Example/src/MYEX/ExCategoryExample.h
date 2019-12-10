#pragma once

#include "ExCategoryBase.h"

class CExCategoryExample : public CExCategoryBase
{
public:
	CExCategoryExample();
	virtual ~CExCategoryExample();

public:
	virtual void SetMenu(CMFCRibbonBar * pRibbonBar) override;

protected:
	CMFCRibbonBar* m_pRibbonBar;


};

