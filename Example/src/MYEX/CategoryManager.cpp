#include "stdafx.h"
#include "CategoryManager.h"
#include "CategoryExample.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CCategoryManager::CCategoryManager()
{
	m_mCategory[E_CAT_EXAMPLE] = std::make_shared<CCategoryExample>();
}

CCategoryManager::~CCategoryManager()
{
	m_mCategory.clear();
}

void CCategoryManager::SetMenu(CMFCRibbonBar * pRibbonBar)
{
	for (auto pair : m_mCategory)
		pair.second->SetMenu(pRibbonBar);
}