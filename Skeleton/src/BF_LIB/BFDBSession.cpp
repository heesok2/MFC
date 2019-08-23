#include "stdafx.h"
#include "BFDBSession.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFDBSession::CBFDBSession(void) : m_lDataPoolCnt(0), m_bTransaction(FALSE)
{
	memset( m_aDataPoolSeq, 0, sizeof(m_aDataPoolSeq) );
	memset( m_aDataPool, 0, sizeof(m_aDataPool) );
}

CBFDBSession::~CBFDBSession(void)
{
	for(long i=0; i<m_lDataPoolCnt; i++)
	{
		auto pPoolBase = GetDataPoolBySeq(i);
		_SAFE_DELETE( pPoolBase );
	}

	memset( m_aDataPool, 0, sizeof(DPoolBase*) * DATATYPE_MAX );
	memset( m_aDataPoolSeq, 0, sizeof(UINT) * DATATYPE_MAX );
}

void CBFDBSession::SetDataPool(UINT uiDataType, DPoolBase* pDataPool)
{
	m_aDataPoolSeq[ uiDataType ] = m_lDataPoolCnt;
	m_aDataPool[ m_lDataPoolCnt++ ] = pDataPool;
}

void CBFDBSession::AttachedDataPool()
{
	ComposedFirst();

	ComposedDataPool();

	ComposedLast();
}

void CBFDBSession::ComposedDataPool()
{
	// Unknown
}

DPoolBase* CBFDBSession::GetDataPool(UINT usDataType)
{
	ASSERT( usDataType < DATATYPE_MAX  );
	if( m_aDataPool[m_aDataPoolSeq[usDataType]] == NULL ) { ASSERT(0); return NULL; }
	if( m_aDataPool[m_aDataPoolSeq[usDataType]]->GetDataType() != usDataType )
	{
		// Who-Soon Hwang
		// 요기 들어오는 DataType은 NXDmain/NXDDBSession에 등록이 제대로 되지 않은 것임!!
		return NULL;
	}
	return m_aDataPool[m_aDataPoolSeq[usDataType]];
}

DPoolBase* CBFDBSession::GetDataPoolBySeq(long iSeq)
{
	// return값을 NULL도 허용해야 함 ( Sequence End Check )
	ASSERT( iSeq < DATATYPE_MAX );
	return m_aDataPool[iSeq];
}

void CBFDBSession::PushNotify(TNotify& notify)
{
	m_vNotify.push_back( std::move(notify) );
}

BOOL CBFDBSession::BeginTR(CString strName)
{
	for( long indx=0; indx<DATATYPE_MAX; ++indx )
	{
		if( m_aDataPool[indx] )
			m_aDataPool[indx]->SetFlag( NULL );
	}

	m_vNotify.clear();

	//////////////////////////////////////////////////////////////////////////

	m_bTransaction = TRUE;

	return TRUE;
}

BOOL CBFDBSession::Commit()
{
	for( long indx=0; indx<m_lDataPoolCnt; ++indx )
	{
		if( m_aDataPool[ m_aDataPoolSeq[indx] ] )
			m_aDataPool[ m_aDataPoolSeq[indx] ]->ProcessRelation();
	}

	CNotifyObject obj( &m_vNotify );
	Notify( DB_NOTIFY_UPDATE, (WPARAM)&obj );

	for( long indx=0; indx<m_lDataPoolCnt; ++indx )
	{
		if( m_aDataPool[ m_aDataPoolSeq[indx] ] )
			m_aDataPool[ m_aDataPoolSeq[indx] ]->DelayDelete();
	}

	//////////////////////////////////////////////////////////////////////////

	m_bTransaction = FALSE;

	return TRUE;
}

BOOL CBFDBSession::Rollback()
{
	//////////////////////////////////////////////////////////////////////////

	m_bTransaction = FALSE;

	return FALSE;
}
