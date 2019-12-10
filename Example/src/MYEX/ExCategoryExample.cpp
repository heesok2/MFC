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

	m_pPanel = m_pCategory->AddPanel(_T("ExPanel"));
	m_pPanel->SetCenterColumnVert(TRUE);

	m_pButtonL = new CMFCRibbonButton(ID_PANEL_BUTTON_L, _T("ExButton Large"), -1, 0);
	m_pButtonL->SetToolTipText(_T("ExButton Large ToolTip"));
	m_pButtonL->SetDescription(_T("ExButton Large Description"));
	m_pPanel->Add(m_pButtonL);

	m_pButtonS = new CMFCRibbonButton(ID_PANEL_BUTTON_S, _T("ExButton Small"), 0, -1);
	m_pButtonS->SetToolTipText(_T("ExButton Small ToolTip"));
	m_pButtonS->SetDescription(_T("ExButton Small Description"));
	m_pPanel->Add(m_pButtonS);	
}
