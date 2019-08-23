#include "stdafx.h"
#include "BFPDBSession.h"

#include "..\BF_DATA\DPoolTest.h"
#include "..\BF_DATA\DPoolTest2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFPDBSession::CBFPDBSession(void)
{
}

CBFPDBSession::~CBFPDBSession(void)
{
}

template<class T>
void ComposeDataPool( CBFDBSession* pDBSession, T* pDPool ) 
{
	ASSERT( pDPool );
	pDBSession->SetDataPool( pDPool->GetDataType(), pDPool );
};

void CBFPDBSession::ComposedDataPool()
{
	ComposeDataPool( this, new DPoolTest(this, DATATYPE_TEST) );
	ComposeDataPool( this, new DPoolTest2(this, DATATYPE_TEST2) );
}