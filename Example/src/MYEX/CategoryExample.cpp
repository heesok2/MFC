#include "stdafx.h"
#include "Resource.h"
#include "CategoryExample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCategoryExample::CCategoryExample()
	: m_pRibbonBar(nullptr)
{
	m_Menu.CreateMenu();
}

CCategoryExample::~CCategoryExample()
{
	m_Menu.DestroyMenu();
}

void CCategoryExample::SetMenu(CMFCRibbonBar * pRibbonBar)
{
	m_pRibbonBar = pRibbonBar;
	m_pCategory = pRibbonBar->AddCategory(_T("Category"), IDB_MENU_EXAMPLE_SMALL, IDB_MENU_EXAMPLE_LARGE);

	m_pPanel = m_pCategory->AddPanel(_T("Panel"));
	m_pPanel->SetCenterColumnVert(TRUE);
	
	m_pBtnExampleDB = new CMFCRibbonButton(ID_MYEX_DB_EXAMPLE, _T("DB Example"), -1, 0);
	m_pBtnExampleDB->SetToolTipText(_T("DB Example ToolTip"));
	m_pBtnExampleDB->SetDescription(_T("DB Example Description"));
	m_pPanel->Add(m_pBtnExampleDB);

	m_pBtnDialog = new CMFCRibbonButton(ID_MYEX_DIALOG, _T("Dialog Example"), 0, -1);
	m_pBtnDialog->SetToolTipText(_T("Dialog Example ToolTip"));
	m_pBtnDialog->SetDescription(_T("Dialog Example Description"));
	m_pPanel->Add(m_pBtnDialog);

	m_pBtnPlugin = new CMFCRibbonButton(ID_MYEX_PLUGIN_UI, _T("Plugin UI"), 0, -1);
	m_pBtnPlugin->SetToolTipText(_T("Plugin UI ToolTip"));
	m_pBtnPlugin->SetDescription(_T("Plugin UI Description"));
	m_pPanel->Add(m_pBtnPlugin);

	m_pBtnGoogleTest = new CMFCRibbonButton(ID_MYEX_GTEST, _T("Google Test "), 0, -1);
	m_pBtnGoogleTest->SetToolTipText(_T("Google Test ToolTip"));
	m_pBtnGoogleTest->SetDescription(_T("Google Test Description"));
	m_pPanel->Add(m_pBtnGoogleTest);	

	m_pBtnAssimp = new CMFCRibbonButton(ID_MYEX_ASSIMPIMPORT, _T("Assimp Import"), 0, -1);
	m_pBtnAssimp->SetToolTipText(_T("Assimp Import ToolTip"));
	m_pBtnAssimp->SetDescription(_T("Assimp Import Description"));
	m_pPanel->Add(m_pBtnAssimp);	
}
