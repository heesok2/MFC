#include "stdafx.h"
#include "BFPMainCategoryManager.h"
#include "BFPMainCategorySample.h"
#include "BFPMainCategorySample2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFPMainCategoryManager::CBFPMainCategoryManager(void)
{
	m_mapCategory[ CT_SAMPLE ] = new CBFPMainCategorySample();
	m_mapCategory[ CT_SAMPLE2 ] = new CBFPMainCategorySample2();
}

CBFPMainCategoryManager::~CBFPMainCategoryManager(void)
{
	for( long indx=0; indx<CT_NUM; ++indx )
	{
		if( m_mapCategory[indx] ) delete m_mapCategory[indx];
	}
}

void CBFPMainCategoryManager::SetMenu(CMFCRibbonBar* pRibbonBar)
{
	for( long indx=0; indx<CT_NUM; ++indx )
	{
		if( m_mapCategory[indx] ) 
			m_mapCategory[indx]->SetMenu(pRibbonBar);
	}
}