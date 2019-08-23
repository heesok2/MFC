#pragma once

#include "TArray.hpp"
#include "BFBaseDataIO.h"

class CBFDBSession;
class DPoolBase;
class CDataBase
{
public:
	CDataBase() {}
	virtual ~CDataBase() {}

public:
	TKey GetKey() const		{ return *((TKey*)((char*)this + VFPTR_SIZE)); }
	void SetKey( TKey key )	{ *((TKey*)((char*)this + VFPTR_SIZE)) = key;  }

public:
	virtual UINT GetDataType() = 0;

	virtual void Init() = 0;

	virtual BOOL KeyToIterator(CBFDBSession* pDBSession) = 0;
	virtual BOOL IteratorToKey(CBFDBSession* pDBSession) = 0;

protected:
	inline void CONVERT_KEY_TO_ITR( DPoolBase* pDPoolBase, TIterator& itr )
	{
		ASSERT( pDPoolBase );
		itr = pDPoolBase->Find( itr );
	}

	inline void CONVERT_ITR_TO_KEY( TIterator& itr )
	{
		if( ITR_IS_VALID(itr) )
			itr = ITR_TO_KEY(itr);
	}

	inline void CONVERT_KEYS_TO_ITRS( DPoolBase* pDPoolBase, TArrayITR& taItr )
	{
		ASSERT( pDPoolBase );

		long lSize = taItr.GetSize();
		for( long indx=0; indx<lSize; ++indx )
			taItr[indx] = pDPoolBase->Find(taItr[indx]);
	}

	inline void CONVERT_ITRS_TO_KEYS( TArrayITR& taItr )
	{
		long lSize = taItr.GetSize();
		for( long indx=0; indx<lSize; ++indx )
		{
			if( ITR_IS_VALID(taItr[indx]) )
				taItr[indx] = ITR_TO_KEY(taItr[indx]);
		}
	}
};