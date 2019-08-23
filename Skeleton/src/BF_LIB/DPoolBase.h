#pragma once

#include "HeaderPre.h"

#define DPOOL_FLAG_ITEMUNKNOWN  0x0000	
#define DPOOL_FLAG_ITEMADDED	0x0001	// Added Flag
#define DPOOL_FLAG_ITEMDELED	0x0002	// Deleted Flag
#define DPOOL_FLAG_ITEMMODED	0x0004	// Modified Flag
#define DPOOL_FLAG_ITEMCHNED	0x0008	// No Change Flag

struct DATA_IO;
class CDataBase;
class CBFDBSession;
class __MY_EXT_CLASS__ DPoolBase
{
public:
	DPoolBase( CBFDBSession* pDBSession, UINT uiDataType );
	virtual ~DPoolBase(void);

public:
	virtual UINT GetDataType() { return m_uiDataType; }
	virtual UINT GetFlag() { return m_uiFlag; }
	virtual void SetFlag( UINT uiFlag ) { m_uiFlag = uiFlag; }

public:
	virtual const DATA_IO* GetDataIO() = 0;
	virtual CDataBase* GetDefaultData( TIterator itr = NULL ) = 0;

public:
	virtual BOOL ProcessRelation() { return TRUE; }
	virtual void DelayDelete() {}

	virtual long GetSize() const = 0;
	virtual BOOL IsEmpty() const = 0;
	virtual TIterator Find( TKey key ) const = 0;
	virtual long GetKeyList( TArrayK& taKey ) = 0;
	virtual long GetItrList( TArrayITR& taItr ) = 0;
	virtual TIterator InsertNU( CDataBase* pData ) = 0;
	virtual BOOL SetAtNU( TIterator itr, CDataBase* pData ) = 0;
	
protected:
	CBFDBSession* m_pDBSession;
	UINT m_uiDataType;
	UINT m_uiFlag;
};

#include "HeaderPost.h"