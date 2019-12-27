#include "stdafx.h"
#include "Resource.h"
#include "ExCategoryExample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExCategoryExample::CExCategoryExample()
	: m_pRibbonBar(nullptr)
{
	m_Menu.CreateMenu();
}

CExCategoryExample::~CExCategoryExample()
{
	m_Menu.DestroyMenu();
}

void CExCategoryExample::SetMenu(CMFCRibbonBar * pRibbonBar)
{
	m_pRibbonBar = pRibbonBar;
	m_pCategory = pRibbonBar->AddCategory(_T("Category"), IDB_MENU_EXAMPLE_SMALL, IDB_MENU_EXAMPLE_LARGE);

	m_pPanel = m_pCategory->AddPanel(_T("Panel"));
	m_pPanel->SetCenterColumnVert(TRUE);
	
	m_pbtnDialog = new CMFCRibbonButton(ID_MYEX_DIALOG, _T("Dialog Example"), -1, 0);
	m_pbtnDialog->SetToolTipText(_T("Dialog Example ToolTip"));
	m_pbtnDialog->SetDescription(_T("Dialog Example Description"));
	m_pPanel->Add(m_pbtnDialog);

	m_pButtonL = new CMFCRibbonButton(ID_MYEX_PLUGIN_UI, _T("Plugin UI"), -1, 0);
	m_pButtonL->SetToolTipText(_T("Plugin UI ToolTip"));
	m_pButtonL->SetDescription(_T("Plugin UI Description"));
	m_pPanel->Add(m_pButtonL);

	m_pButtonS = new CMFCRibbonButton(ID_MYEX_GTEST, _T("Google Test "), 0, -1);
	m_pButtonS->SetToolTipText(_T("Google Test ToolTip"));
	m_pButtonS->SetDescription(_T("Google Test Description"));
	m_pPanel->Add(m_pButtonS);	
}
