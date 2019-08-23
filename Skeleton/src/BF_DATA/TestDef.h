#pragma once


#include "..\BF_LIB\DataBase.hpp"

#include "BFDataType.h"
#include "HeaderPre.h"
#pragma pack(push, 4)

#define T_DEFAULT_HASH_SIZE_TEST 1000

struct __MY_EXT_CLASS__ TTestSub
{
	int nData;
	double dData;
	TArrayITR taItr;

	void Init()
	{
		nData = 0;
		dData = 0;
		taItr.RemoveAll();
	}

	TTestSub& operator=( const TTestSub& src )
	{
		nData = src.nData;
		dData = src.dData;
		taItr = src.taItr;

		return *this;
	}

	BEGIN_DATA_IO( TTestSub )
		DATA_IO_DEFN_FIXD( _N_DATA,		TTestSub, int, nData ),
		DATA_IO_DEFN_FIXD( _D_DATA,		TTestSub, double, dData ),
		DATA_IO_ARRY_ITER( _TARR_ITR,	TTestSub, TArrayITR, taItr, TIterator ),
		DATA_IO_LAST();
	END_DATA_IO();
}; 

struct __MY_EXT_CLASS__ TTestData
{
	int nData;
	double dData;
	TArrayITR taItr;
	TTestSub tSubData;

	void Init()
	{
		nData = 0;
		dData = 0;
		taItr.RemoveAll();
		tSubData.Init();
	}

	BEGIN_DATA_IO( TTestData )
		DATA_IO_DEFN_FIXD( _N_DATA,		TTestData, int, nData ),
		DATA_IO_DEFN_FIXD( _D_DATA,		TTestData, double, dData ),
		DATA_IO_ARRY_ITER( _TARR_ITR,	TTestData, TArrayITR, taItr, TIterator ),
		DATA_IO_DEFN_STRT( _SUB,		TTestData, TTestSub, tSubData ),
		DATA_IO_LAST();
	END_DATA_IO();

}; 

typedef TArray<TTestData> TArrayTestD;

/*
Array > Array �� ����Ϸ��� 
1. =operator �� ������. 
=> Array �ȿ� �ִ� Array �� ���� ���縦 �Ѵ�.
2. �Ҹ��ڿ��� �޸� ���� ������ �߰�����.
=> Array �ȿ� �ִ� Array �޸� ������ ���� �ʴ´�.
*/

class __MY_EXT_CLASS__ CTest : public CDataBase
{
public:
	TKey Key; // Key�� ������ ù��° ����
	TVector3d vPos;
	TTestData tData;
	TArrayTestD taData;

	BEGIN_DATA_IO( CTest )
		DATA_IO_DEFN_FIXD( _KEY, CTest, TKey, Key ),
		DATA_IO_DEFN_FIXD( _POS, CTest, TVector3d, vPos ),
		DATA_IO_DEFN_STRT( _DATA, CTest, TTestData, tData ),
		DATA_IO_ARRY_STRT( _TARR_DATA, CTest, TArrayTestD, taData, TTestData ),
		DATA_IO_LAST();
	END_DATA_IO();

public:
	CTest() { Init(); }
	CTest( const CTest& src) { *this = src; }
	virtual ~CTest() { Init(); }

	CTest& operator=( const CTest& src )
	{
		Key = src.Key;
		vPos = src.vPos;
		tData = src.tData;

		long lSize = src.taData.GetSize();
		taData.SetSize( lSize );

		for( long indx=0; indx<lSize; ++indx )
		{
			taData[indx] = src.taData[indx];
		}

		return *this;
	}

public:
	virtual UINT GetDataType() { return DATATYPE_TEST; }

	virtual void Init() 
	{ 
		Key = 0;
		vPos.Set(0.);
		tData.Init();

		long lSize = taData.GetSize();
		for( long indx=0; indx<lSize; ++indx )
		{
			taData[indx].Init();
		}

		taData.RemoveAll();
	}

	virtual BOOL KeyToIterator(CBFDBSession* pDBSession)
	{
		return TRUE;
	}

	virtual BOOL IteratorToKey(CBFDBSession* pDBSession)
	{
		return TRUE;
	}

};

#pragma pack(pop)
#include "HeaderPost.h"