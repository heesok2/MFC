#include "stdafx.h"
#include "DPoolBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

DPoolBase::DPoolBase(CBFDBSession* pDBSession, UINT uiDataType)
	: m_pDBSession( pDBSession ), m_uiDataType( uiDataType ), m_uiFlag(NULL)
{
}

DPoolBase::~DPoolBase(void)
{
}