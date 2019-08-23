#pragma once

class CBFPMainCategoryBase
{
public:
	CBFPMainCategoryBase(void);
	virtual ~CBFPMainCategoryBase(void);

public:
	virtual void SetMenu( CMFCRibbonBar* pRibbonBar ) { ASSERT(0); }

protected:
	CMFCToolBarImages m_tbImags;
};