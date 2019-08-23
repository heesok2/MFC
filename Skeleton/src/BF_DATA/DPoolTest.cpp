#include "stdafx.h"
#include "DPoolTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DPoolTest::DPoolTest(CBFDBSession* pDBSession, UINT uiDataType)
	: DPool<CTest>( pDBSession, uiDataType, T_DEFAULT_HASH_SIZE_TEST )
{

}

DPoolTest::~DPoolTest(void)
{

}