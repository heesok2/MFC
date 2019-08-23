#pragma once

#include "BFBaseDataDef.h"

template <class DATA_ITEM>
class CDataLinker
{
public:
	typedef struct tagObjectData
	{
		ObjectParam		param;
		DATA_ITEM		data;

		// hash table list
		struct tagObjectData* hprev;
		struct tagObjectData* hnext;

		// data linked list
		struct tagObjectData* lprev;
		struct tagObjectData* lnext;

	} ObjectData, *LPObjectData;

public:
	CDataLinker(void) : m_lDataSize(0), m_pHead(nullptr), m_pTail(nullptr),
		m_lHashSize(DLINKER_HASH_SIZE), m_pHashTable(nullptr),
		m_lMinKey(0), m_lMaxKey(0)
	{
		m_pHashTable = new LPObjectData[m_lHashSize];
		memset( m_pHashTable, 0, sizeof(LPObjectData) * m_lHashSize );
	}

	CDataLinker(long lHashSize) : m_lDataSize(0), m_pHead(nullptr), m_pTail(nullptr),
		m_lHashSize(lHashSize), m_pHashTable(nullptr) ,
		m_lMinKey(0), m_lMaxKey(0)
	{
		if( m_lHashSize < DLINKER_HASH_SIZE ) m_lHashSize = DLINKER_HASH_SIZE;

		m_pHashTable = new LPObjectData[m_lHashSize];
		memset( m_pHashTable, 0, sizeof(LPObjectData) * m_lHashSize );
	}

	~CDataLinker(void)
	{
		DeleteAll();

		DeleteHash();		
	}

public:
	long GetSize() const
	{ 
		return m_lDataSize; 
	}

	BOOL IsEmpty() const
	{
		return m_lDataSize == 0; 
	}

	TIterator Find( TKey key ) const 
	{
		if( !KEY_IS_VALID(key) ) return (TIterator)nullptr;

		long indx = DLINKER_HASH_INDX( key, m_lHashSize );

		LPObjectData pData = m_pHashTable[ indx ];
		while( pData != nullptr )
		{
			if( pData->data.GetKey() == key )
				return (TIterator)pData;

			pData = pData->hnext;			
		}

		return (TIterator)nullptr;
	}

	long GetKeyList( TArrayK& taKey )
	{
		taKey.RemoveAll();

		if( m_lDataSize == 0 ) return 0;

		long idx=0;
		taKey.SetSize( m_lDataSize );

		for(LPObjectData pItem = m_pHead; pItem != NULL; pItem = pItem->lnext)
		{
			taKey[idx++] = pItem->data.GetKey();
		}

		ASSERT( m_lDataSize == idx );
		return m_lDataSize;
	}

	long GetItrList( TArrayITR& taItr ) 
	{ 
		taItr.RemoveAll();

		if( m_lDataSize == 0 ) 
			return 0;

		long idx=0;
		taItr.SetSize( m_lDataSize );

		for(LPObjectData pItem = m_pHead; pItem != NULL; pItem = pItem->lnext)
		{
			taItr[idx++] = (TIterator)pItem;
		}

		ASSERT( m_lDataSize == idx );
		return m_lDataSize;
	}

	TIterator GetHeadPosition() const 
	{ 
		return (TIterator)m_pHead; 
	}

	void Prev( TIterator& itr ) const
	{
		if( ITR_IS_VALID(itr) ) 
			itr = (TIterator)(((ObjectData*)itr)->lprev);
	}

	void Next( TIterator& itr ) const
	{
		if( ITR_IS_VALID(itr) ) 
			itr = (TIterator)(((ObjectData*)itr)->lnext);
	}

	const DATA_ITEM& GetAtNU( TIterator itr ) const 
	{ 
		return ((ObjectData*)itr)->data; 
	}

	TIterator InsertNU( const DATA_ITEM& data )
	{
		TKey key = data.GetKey();

		if( !KEY_IS_VALID(key) ) { ASSERT(0); return (TIterator)nullptr; }
		if( Find(key) ) { ASSERT(0); return (TIterator)nullptr; }

		ObjectData* pData = new ObjectData;
		pData->data = data;

		InsertHash( pData );
		InsertData( pData );

		SetMinMaxKey( key );
		m_lDataSize++;

		return (TIterator)pData;
	}

	BOOL SetAtNU( TIterator itr, const DATA_ITEM& data )
	{
		if( !ITR_IS_VALID(itr) ) { ASSERT(0); return FALSE; }

		TKey orgK = ((ObjectData*)itr)->data.GetKey();
		TKey curK = data.GetKey();

		if( !KEY_IS_VALID(curK) ) { ASSERT(0); return FALSE; }
		if( orgK != curK )
		{
			TIterator itrOrg = Find(orgK);
			if( !ITR_IS_VALID(itrOrg) ) { ASSERT(0); return FALSE; }
			if( itrOrg != itr ) { ASSERT(0); return FALSE; }

			ObjectData* pData = (ObjectData*)itr;
			RemoveHash( pData );
			pData->data = data;
			InsertHash( pData );

			SetMinMaxKey( curK );
		}
		else
		{
			((ObjectData*)itr)->data = data;
		}

		return TRUE;
	}

	BOOL Remove( const TIterator& itr )
	{
		if( !ITR_IS_VALID(itr) ) { ASSERT(0); return FALSE; }

		register auto pData = (LPObjectData)itr;

		RemoveHash( pData );
		RemoveData( pData );

		_SAFE_DELETE(pData);
		m_lDataSize--;

		return TRUE;
	}

	BOOL RemoveNext( TIterator& itr )
	{
		if( !ITR_IS_VALID(itr) ) { ASSERT(0); return FALSE; }

		register auto pData = (LPObjectData)itr;

		RemoveHash( pData );
		RemoveData( pData );

		itr = (TIterator)pData->lnext;

		_SAFE_DELETE(pData);
		m_lDataSize--;		

		return TRUE;
	}


	BOOL RemoveWithoutDelete( const TIterator& itr )
	{
		if( !ITR_IS_VALID(itr) ) { ASSERT(0); return FALSE; }

		register auto pData = (LPObjectData)itr;

		RemoveHash( pData );
		RemoveData( pData );

		pData->param.removed = __OBJ_PARAM_ON___;
		m_lDataSize--;

		return TRUE;
	}

	BOOL RemoveNextWithoutDelete( TIterator& itr )
	{
		if( !ITR_IS_VALID(itr) ) { ASSERT(0); return FALSE; }

		register auto pData = (LPObjectData)itr;

		RemoveHash( pData );
		RemoveData( pData );

		itr = (TIterator)pData->lnext;

		pData->param.removed = __OBJ_PARAM_ON___;
		m_lDataSize--;		

		return TRUE;
	}

	void SetDefaultHashSize(long nHashSizeDefault)
	{
		_SAFE_DELETE_ARRAY( m_pHashTable );

		m_lHashSize = nHashSizeDefault;

		m_pHashTable = new LPObjectData[m_lHashSize];
		memset( m_pHashTable, 0, sizeof(LPObjectData) * m_lHashSize );

		RebuildHash();
	}

	void RebuildHash()
	{
		memset( m_pHashTable, 0, sizeof(LPObjectData)*m_lHashSize );

		register long   idxHash;
		register LPObjectData pItem = m_pHead;

		while(pItem != 0)
		{
			idxHash = DLINKER_HASH_INDX( pItem->data.GetKey(), m_lHashSize );

			// insert to hash ( push front )
			pItem->hprev			= 0;
			pItem->hnext			= m_pHashTable[idxHash];
			m_pHashTable[idxHash]	= pItem; 
			// by jbseon : Optimize 안 된 상태에서 Rebuild Hash가 호출되면 Prev 연결 관계 문제 발생
			if (pItem->hnext != NULL) pItem->hnext->hprev = pItem;  

			pItem = pItem->lnext;
		}
	}

	TKey GetMaxKey() 
	{ 
		return m_lMaxKey; 
	}

	TKey GetNewKey() 
	{ 
		return GetMaxKey() + 1; 
	}

protected:

#pragma region FUNCTION

	void SetMinMaxKey( TKey key )
	{
		if( m_lDataSize == 0 )
		{
			m_lMinKey = key;
			m_lMaxKey = key;
		}
		else
		{
			m_lMinKey = ( key < m_lMinKey ) ? key : m_lMinKey;
			m_lMaxKey = ( key > m_lMaxKey ) ? key : m_lMaxKey;
		}
	}

#pragma endregion

#pragma region LINKED_LIST

	void InsertData( LPObjectData pData )
	{
		if( m_pHead == nullptr )
		{
			pData->lprev = nullptr;
			pData->lnext = nullptr;

			m_pHead = pData;
			m_pTail = pData;
		}
		else
		{
			pData->lprev = m_pTail;
			pData->lnext = nullptr;
			if( m_pTail ) 
				m_pTail->lnext = pData;

			m_pTail = pData;
		}
	}

	void RemoveData( LPObjectData pData )
	{
		if( pData->lprev ) pData->lprev->lnext = pData->lnext;
		else m_pHead = pData->lnext;

		if( pData->lnext ) pData->lnext->lprev = pData->lprev;
		else m_pTail = pData->lprev;
	}

	void DeleteAll()
	{
		memset( m_pHashTable, 0, sizeof(LPObjectData)*m_lHashSize );

		LPObjectData pData = m_pHead;
		LPObjectData pNext = nullptr;
		while( pData != nullptr )
		{
			pNext = pData->lnext;
			_SAFE_DELETE(pData);
			pData = pNext;
		}

		m_lDataSize = 0;
		m_pHead = nullptr;
		m_pTail = nullptr;

		m_lMinKey = 0;
		m_lMaxKey = 0;
	}

	void InsertHash( LPObjectData pData )
	{
		long index = DLINKER_HASH_INDX( pData->data.GetKey(), m_lHashSize );
		LPObjectData pHash = m_pHashTable[ index ];

		pData->hprev = nullptr;
		pData->hnext = pHash;
		if( pHash ) pHash->hprev = pData;

		m_pHashTable[ index ] = pData;
	}

	void RemoveHash( LPObjectData pData )
	{
		long index = DLINKER_HASH_INDX( pData->data.GetKey(), m_lHashSize );
		LPObjectData pHash = m_pHashTable[ index ];

		if( pData->hprev == nullptr ) 
			m_pHashTable[ index ] = pData->hnext;
		else 
			pData->hprev->hnext = pData->hnext;

		if( pData->hnext != nullptr )
			pData->hnext->hprev = pData->hprev;
	}

	void DeleteHash() 
	{
		_SAFE_DELETE_ARRAY( m_pHashTable );

		m_lHashSize = 0;
		m_pHashTable = nullptr;
	}

#pragma endregion

protected:
	long m_lDataSize;
	LPObjectData m_pHead;
	LPObjectData m_pTail;

	long m_lHashSize;
	LPObjectData* m_pHashTable;

	long m_lMinKey;
	long m_lMaxKey;
};