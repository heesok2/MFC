#pragma once

#include "BFPMainCategoryBase.h"

class CBFPMainCategorySample : public CBFPMainCategoryBase
{
public:
	CBFPMainCategorySample(void);
	virtual ~CBFPMainCategorySample(void);

public:
	virtual void SetMenu( CMFCRibbonBar* pRibbonBar );

private:
	void MakeMenu( CMFCRibbonButton* pRibbonButton );

private:
	CMFCRibbonBar*			m_pRibbonBar;
	CMFCRibbonCategory*		m_pCategory;
	
	CMFCRibbonPanel*		m_pPanelT1;
	CMFCRibbonButton*		m_pButtonT1;
	CMFCRibbonCheckBox*		m_pCheckBoxT1;
	CMFCRibbonComboBox*		m_pComboBoxT1;
	CMFCRibbonComboBox*		m_pComboBoxT2;

	CMFCRibbonPanel*		m_pPanelT2;
	CMFCRibbonButton*		m_pButtonMenu;
	CMenu					m_Menu;
};