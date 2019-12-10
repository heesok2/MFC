#include "stdafx.h"
#include "ExCategoryManager.h"
#include "ExCategoryExample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExCategoryManager::CExCategoryManager()
{
	m_mCategory[E_CAT_EXAMPLE] = std::make_shared<CExCategoryExample>();
}

CExCategoryManager::~CExCategoryManager()
{
	m_mCategory.clear();
}

void CExCategoryManager::SetMenu(CMFCRibbonBar * pRibbonBar)
{
	for (auto pair : m_mCategory)
		pair.second->SetMenu(pRibbonBar);
}