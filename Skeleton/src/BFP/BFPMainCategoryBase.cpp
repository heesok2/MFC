#include "stdafx.h"
#include "BFPMainCategoryBase.h"
#include "BFPRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFPMainCategoryBase::CBFPMainCategoryBase(void)
{
 	m_tbImags.SetImageSize( CSize(16, 16) );
 	m_tbImags.Load( IDB_BFPMAIN_RIBM_BTN );
}


CBFPMainCategoryBase::~CBFPMainCategoryBase(void)
{
}
