#include "stdafx.h"
#include "DPoolTest2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DPoolTest2::DPoolTest2(CBFDBSession* pDBSession, UINT uiDataType)
	: DPool<CTest2>( pDBSession, uiDataType, T_DEFAULT_HASH_SIZE_TEST2 )
{

}

DPoolTest2::~DPoolTest2(void)
{

}

BOOL DPoolTest2::ProcessRelation()
{
	auto pDPoolTest = m_pDBSession->GetDataPool( DATATYPE_TEST ); ASSERT( pDPoolTest );
	
	auto bCheck = pDPoolTest->GetFlag() & DPOOL_FLAG_ITEMDELED;
	if( !bCheck ) return TRUE;
	
	auto itr = GetHeadPosition();
	while( ITR_IS_VALID(itr) )
	{

		Next(itr);
	}

	return TRUE;
}
