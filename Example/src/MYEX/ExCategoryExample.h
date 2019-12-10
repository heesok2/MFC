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
	CMFCRibbonCategory*	m_pCategory;

	CMFCRibbonPanel* m_pPanel;
	CMFCRibbonButton* m_pButtonL;
	CMFCRibbonButton* m_pButtonS;
	CMFCRibbonCheckBox* m_pCheckBox;
	CMFCRibbonComboBox*	m_pComboBox;
	CMFCRibbonButton* m_pButtonMenu;
	CMenu m_Menu;

};