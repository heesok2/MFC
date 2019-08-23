#include "stdafx.h"
#include "BFPMainCategorySample2.h"
#include "BFPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFPMainCategorySample2::CBFPMainCategorySample2(void)
{
}


CBFPMainCategorySample2::~CBFPMainCategorySample2(void)
{
}

void CBFPMainCategorySample2::SetMenu(CMFCRibbonBar* pRibbonBar)
{
 	m_pRibbonBar = pRibbonBar;
 
 	m_pCategory = pRibbonBar->AddCategory( _T("Category"), IDB_BFPMAIN_RIBM_SMALL, IDB_BFPMAIN_RIBM_LARGE );
 
 	m_pPanelT1 = m_pCategory->AddPanel( _T("Panel"), m_tbImags.ExtractIcon(27) );
 	m_pPanelT1->SetCenterColumnVert(TRUE);
 
 	m_pButtonT1 = new CMFCRibbonButton( ID_BFPMAIN_RIBM_BUTTON3, _T("Button3"), 0, -1 );
 	m_pButtonT1->SetToolTipText( _T("Button3 ToolTip"));
 	m_pButtonT1->SetDescription( _T("Button3 Description"));
 	m_pPanelT1->Add( m_pButtonT1 );
 
 	m_pPanelT2 = m_pCategory->AddPanel( _T("Panel"), m_tbImags.ExtractIcon(27) );
 	m_pPanelT2->SetCenterColumnVert(TRUE);
 
 	m_pButtonT2 = new CMFCRibbonButton( ID_BFPMAIN_RIBM_BUTTON4, _T("Button4"), 0, 0 );
 	m_pButtonT2->SetToolTipText( _T("Button4 ToolTip"));
 	m_pButtonT2->SetDescription( _T("Button4 Description"));
 	m_pPanelT2->Add( m_pButtonT2 );
}