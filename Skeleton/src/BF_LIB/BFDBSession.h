#pragma once

#include "BFNotifyDef.h"
#include "BFNotifyManager.h"
#include "DPoolBase.h"
#include "HeaderPre.h"

#define DATATYPE_MAX 2048

class __MY_EXT_CLASS__ CBFDBSession : public CBFNotifyManager
{
	friend class CTransaction;

public:
	CBFDBSession(void);
	virtual ~CBFDBSession(void);

public:
	virtual void SetDataPool( UINT uiDataType, DPoolBase* pDataPool );
	virtual void AttachedDataPool();

protected:
	virtual void ComposedDataPool(); 
	virtual void ComposedFirst() {} // 특별한 경우 만 추가
	virtual void ComposedLast() {} // 특별한 경우 만 추가

public:
	long GetCount() { return m_lDataPoolCnt; }
	DPoolBase* GetDataPool( UINT usDataType );
	DPoolBase* GetDataPoolBySeq( long iSeq );

public:
	BOOL IsTR() { return m_bTransaction; }
	void SetTR( BOOL bTR ) { m_bTransaction = bTR; }
	void PushNotify( TNotify& notify );

protected:
	BOOL BeginTR( CString strName );
	BOOL Commit();
	BOOL Rollback();

protected:
	long m_lDataPoolCnt;
	long m_aDataPoolSeq[ DATATYPE_MAX ];
	DPoolBase* m_aDataPool[ DATATYPE_MAX ];

	BOOL m_bTransaction;
	VEC_NOTIFY m_vNotify;
};

class __MY_EXT_CLASS__ CTransaction 
{
public:
	CTransaction( CBFDBSession* pDBSession ) 
		: m_pDBSession(pDBSession) { }

	virtual ~CTransaction(void)
	{ ASSERT( !m_pDBSession->IsTR() ); if( m_pDBSession->IsTR() ) Rollback(); }

public:
	BOOL Begin( CString strName ) 
	{ ASSERT( !m_pDBSession->IsTR() ); return m_pDBSession->BeginTR(strName); }

	BOOL Commit() 
	{ ASSERT( m_pDBSession->IsTR() ); return m_pDBSession->Commit(); }

	BOOL Rollback() 
	{ ASSERT( m_pDBSession->IsTR() ); return m_pDBSession->Rollback(); }

protected:
	CBFDBSession* m_pDBSession;

};

#include "HeaderPost.h"