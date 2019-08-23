#pragma once

#include "..\BF_LIB\DataBase.hpp"

#include "BFDataType.h"
#include "HeaderPre.h"
#pragma pack(push, 4)

#define T_DEFAULT_HASH_SIZE_TEST2 1000

class __MY_EXT_CLASS__ CTest2 : public CDataBase
{
public:
	TKey Key; // Key는 무조건 첫번째 인자
	UINT uiType; // Type of Element
	TArrayITR taItrTest; // Test Iterator Array	

	BEGIN_DATA_IO( CTest2 )
		DATA_IO_DEFN_FIXD( _KEY, CTest2, TKey, Key ),
		DATA_IO_DEFN_FIXD( _POS, CTest2, UINT, uiType ),
		DATA_IO_ARRY_ITER( _ARR_TEST, CTest2, TArrayITR, taItrTest, TIterator ),
		DATA_IO_LAST();
	END_DATA_IO();

public:
	CTest2() { Init(); }
	virtual ~CTest2() {}

public:
	virtual UINT GetDataType() { return DATATYPE_TEST2; }

	virtual void Init() 
	{ 
		Key = 0;
		uiType = 0;
		taItrTest.RemoveAll();
	}

	virtual BOOL KeyToIterator(CBFDBSession* pDBSession)
	{
		auto pDPoolBase = pDBSession->GetDataPool( DATATYPE_TEST );

		CONVERT_KEYS_TO_ITRS( pDPoolBase, taItrTest );

		return TRUE;
	}

	virtual BOOL IteratorToKey(CBFDBSession* pDBSession)
	{
		CONVERT_ITRS_TO_KEYS( taItrTest );

		return TRUE;
	}
};

#pragma pack(pop)
#include "HeaderPost.h"