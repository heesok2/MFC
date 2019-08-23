#include "stdafx.h"
#include "BFPMainCategorySample.h"
#include "BFPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFPMainCategorySample::CBFPMainCategorySample(void)
{
	m_Menu.CreateMenu();
}


CBFPMainCategorySample::~CBFPMainCategorySample(void)
{
	m_Menu.DestroyMenu();
}

void CBFPMainCategorySample::SetMenu(CMFCRibbonBar* pRibbonBar)
{
	m_pRibbonBar = pRibbonBar;

	m_pCategory = pRibbonBar->AddCategory( _T("Category"), IDB_BFPMAIN_RIBM_SMALL, IDB_BFPMAIN_RIBM_LARGE );

	m_pPanelT1 = m_pCategory->AddPanel( _T("Panel"), m_tbImags.ExtractIcon(27) );
	m_pPanelT1->SetCenterColumnVert(TRUE);

	m_pButtonT1 = new CMFCRibbonButton( ID_BFPMAIN_RIBM_BUTTON1, _T("Button1"), 0, -1 );
	m_pButtonT1->SetToolTipText( _T("Button1 ToolTip"));
	m_pButtonT1->SetDescription( _T("Button1 Description"));
	m_pPanelT1->Add( m_pButtonT1 );

	m_pCheckBoxT1 = new CMFCRibbonCheckBox( ID_BFPMAIN_RIBM_CHECKBOX1, _T("Check1") );
	m_pPanelT1->Add( m_pCheckBoxT1 );

	m_pComboBoxT1 = new CMFCRibbonComboBox( ID_BFPMAIN_RIBM_COMBOBOX1, FALSE, 100, _T("ComboBox1"), -1 );
	m_pComboBoxT1->AddItem( _T("Item1"), 1 );
	m_pComboBoxT1->AddItem( _T("Item2"), 2 );
	m_pComboBoxT1->SelectItem(1);
	m_pPanelT1->Add( m_pComboBoxT1 );

	m_pComboBoxT2 = new CMFCRibbonComboBox( ID_BFPMAIN_RIBM_COMBOBOX2, TRUE, 100, _T("ComboBox2"), -1 );
	m_pComboBoxT2->AddItem( _T("Item3"), 3 );
	m_pComboBoxT2->AddItem( _T("Item4"), 4 );
	m_pComboBoxT2->SelectItem(1);
	m_pPanelT1->Add( m_pComboBoxT2 );

	m_pPanelT2 = m_pCategory->AddPanel( _T("Panel2"), m_tbImags.ExtractIcon(27) );
	m_pPanelT2->SetCenterColumnVert(TRUE);

	m_pButtonMenu = new CMFCRibbonButton( ID_BFPMAIN_RIBM_BUTTONMENU, _T("Menu"), 0, -1 );
	MakeMenu( m_pButtonMenu );
	m_pButtonMenu->SetToolTipText( _T("ButtonMenu ToolTip"));
	m_pButtonMenu->SetDescription( _T("ButtonMenu Description"));
	m_pPanelT2->Add( m_pButtonMenu );
}
 
void CBFPMainCategorySample::MakeMenu(CMFCRibbonButton* pRibbonButton)
{
	if( m_Menu.GetMenuItemCount() > 0 )
	{
		pRibbonButton->RemoveAllSubItems();
		m_Menu.ModifyMenu(0, MF_BYPOSITION|MF_BYCOMMAND, ID_BFPMAIN_RIBM_BUTTONMENU1, (wchar_t*)(LPCTSTR)(_T("Menu1")));
		m_Menu.ModifyMenu(1, MF_BYPOSITION|MF_BYCOMMAND, ID_BFPMAIN_RIBM_BUTTONMENU2, (wchar_t*)(LPCTSTR)(_T("Menu2")));
		pRibbonButton->SetMenu(m_Menu.GetSafeHmenu());
	}
	else
	{
		pRibbonButton->RemoveAllSubItems();
		m_Menu.AppendMenu(MF_STRING|MF_BYCOMMAND, ID_BFPMAIN_RIBM_BUTTONMENU1, (wchar_t*)(LPCTSTR)(_T("Menu1")));
		m_Menu.AppendMenu(MF_STRING|MF_BYCOMMAND, ID_BFPMAIN_RIBM_BUTTONMENU2, (wchar_t*)(LPCTSTR)(_T("Menu2")));
		pRibbonButton->SetMenu(m_Menu.GetSafeHmenu());
	}
}
