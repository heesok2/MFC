#include "stdafx.h"
#include "ExCategoryExample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExCategoryExample::CExCategoryExample()
	: m_pRibbonBar(nullptr)
{
}

CExCategoryExample::~CExCategoryExample()
{
}

void CExCategoryExample::SetMenu(CMFCRibbonBar * pRibbonBar)
{
	m_pRibbonBar = pRibbonBar;
}
