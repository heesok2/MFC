#pragma once

#include "BFPMainCategoryBase.h"

class CBFPMainCategorySample2 : public CBFPMainCategoryBase
{
public:
	CBFPMainCategorySample2(void);
	virtual ~CBFPMainCategorySample2(void);

public:
	virtual void SetMenu( CMFCRibbonBar* pRibbonBar );

private:
	CMFCRibbonBar*			m_pRibbonBar;
	CMFCRibbonCategory*		m_pCategory;

	CMFCRibbonPanel*		m_pPanelT1;
	CMFCRibbonButton*		m_pButtonT1;

	CMFCRibbonPanel*		m_pPanelT2;
	CMFCRibbonButton*		m_pButtonT2;
};