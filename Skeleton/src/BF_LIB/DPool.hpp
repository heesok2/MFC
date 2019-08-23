#pragma once

#include "DPoolBase.h"
#include "DataLinker.hpp"

template <class Type>
class DPool : public DPoolBase
{
	static Type* GetInitData() 
	{
		static Type tData;
		return &tData;
	}

public:
	DPool( CBFDBSession* pDBSession, UINT uiDataType, long lHashSize ) 
		: DPoolBase( pDBSession, uiDataType ), m_pool(lHashSize)
	{}
	virtual ~DPool() {}

public:
	virtual const DATA_IO* GetDataIO()
	{
		return Type::GetDataIO();
	}

	virtual CDataBase* GetDefaultData(TIterator itr)
	{
		auto& tData = *DPool::GetInitData();
		if( ITR_IS_VALID(itr) )
			tData = GetAtNU( itr );

		return &tData;
	}

public:
	virtual void DelayDelete() 
	{
		if( m_deleter.empty() ) return;

		for( auto itr : m_deleter )
		{
			auto pData = (CDataLinker<Type>::LPObjectData)itr;
			_SAFE_DELETE( pData );
		}

		m_deleter.clear();
	}

	virtual long GetSize() const
	{ 
		return m_pool.GetSize(); 
	}

	virtual BOOL IsEmpty() const
	{
		return m_pool.IsEmpty();
	}

	virtual TIterator Find( TKey key ) const
	{
		return m_pool.Find(key);
	}
	
	virtual long GetKeyList( TArrayK& taKey )
	{
		return m_pool.GetKeyList( taKey ); 
	}
	
	virtual long GetItrList( TArrayITR& taItr ) 
	{ 
		return m_pool.GetItrList( taItr ); 
	}

	virtual TIterator GetHeadPosition() const
	{
		return m_pool.GetHeadPosition();
	}

	virtual void Prev( TIterator& itr ) const
	{
		m_pool.Prev(itr);
	}

	virtual void Next( TIterator& itr ) const
	{
		m_pool.Next(itr);
	}
	
	virtual const Type& GetAtNU( TIterator itr ) const 
	{
		return m_pool.GetAtNU(itr);
	}

	virtual TIterator InsertNU( const Type& data )
	{
		auto itr = m_pool.InsertNU( data );
		if( ITR_IS_VALID(itr) )
		{
			if( m_pDBSession && m_pDBSession->IsTR() )
			{
				m_uiFlag |= DPOOL_FLAG_ITEMADDED;
				m_pDBSession->PushNotify( TNotify(m_uiDataType, TR_ADD, itr, NULL) );
			}
		}

		return itr;
	}

	virtual BOOL SetAtNU( TIterator itr, const Type& data )
	{
		return m_pool.SetAtNU( itr, data );
	}

	virtual BOOL Remove( const TIterator& itr )
	{
		BOOL bRemove = FALSE;
		if( m_pDBSession && m_pDBSession->IsTR() )
		{
			auto itrDelete = itr;
			bRemove = m_pool.RemoveWithoutDelete( itr );

			if( bRemove )
			{
				m_deleter.push_back( itrDelete );

				m_uiFlag |= DPOOL_FLAG_ITEMDELED;
				m_pDBSession->PushNotify( TNotify(m_uiDataType, TR_DEL, itr, NULL) );
			}
		}
		else
		{
			bRemove = m_pool.Remove( itr );
		}

		return bRemove;
	}

	virtual BOOL RemoveNext( TIterator& itr )
	{
		BOOL bRemove = FALSE;
		if( m_pDBSession && m_pDBSession->IsTR() )
		{
			auto itrDelete = itr;
			bRemove = m_pool.RemoveNextWithoutDelete( itr );

			if( bRemove )
			{
				m_deleter.push_back( itrDelete );

				m_uiFlag |= DPOOL_FLAG_ITEMDELED;
				m_pDBSession->PushNotify( TNotify(m_uiDataType, TR_DEL, itr, NULL) );
			}
		}
		else
		{
			bRemove = m_pool.RemoveNext( itr );
		}

		return bRemove;
	}

	virtual TIterator InsertNU( CDataBase* pData ) // File Read/Write 에서 사용
	{
		return InsertNU( ((Type&)*pData) );
	}

	virtual BOOL SetAtNU( TIterator itr, CDataBase* pData ) // File Read/Write 에서 사용
	{
		return SetAtNU( itr, ((Type&)*pData) );
	}

	virtual void SetDefaultHashSize(long nHashSizeDefault) 
	{
		m_pool.SetDefaultHashSize(nHashSizeDefault); 
	}

	virtual TKey GetNewKey() { return m_pool.GetNewKey(); }

protected:
	CDataLinker<Type> m_pool;
	std::vector<TIterator> m_deleter;
};