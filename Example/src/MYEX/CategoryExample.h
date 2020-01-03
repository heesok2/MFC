#pragma once

#include "CategoryBase.h"

class CCategoryExample : public CCategoryBase
{
public:
	CCategoryExample();
	virtual ~CCategoryExample();

public:
	virtual void SetMenu(CMFCRibbonBar * pRibbonBar) override;

protected:
	CMFCRibbonBar* m_pRibbonBar;
	CMFCRibbonCategory*	m_pCategory;

	CMFCRibbonPanel* m_pPanel;
	CMFCRibbonButton* m_pBtnPlugin;
	CMFCRibbonButton* m_pBtnGoogleTest;
	CMFCRibbonButton* m_pBtnDialog;
	CMFCRibbonButton* m_pBtnAssimp;
	CMFCRibbonButton* m_pBtnExampleDB;

	CMFCRibbonCheckBox* m_pCheckBox;
	CMFCRibbonComboBox*	m_pComboBox;
	CMFCRibbonButton* m_pButtonMenu;
	CMenu m_Menu;

};