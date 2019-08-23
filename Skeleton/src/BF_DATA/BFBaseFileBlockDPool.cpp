#include "stdafx.h"
#include "BFBaseFileBlockDPool.h"
#include "BFDataType.h"

#include "..\BF_LIB\BFBaseFileIO.h"
#include "..\BF_LIB\BFDBSession.h"
#include "..\BF_LIB\DataBase.hpp"
#include "..\BF_BASE\BFDocBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BF_FILE_BLOCK_IMPL( F_BLOCK_VER_100, F_BLOCK_TYPE_DPOOL, CBFBaseFileBlockDPool );

struct TFileBlockDPool
{
	int nDataType;
	int nBulkSize;

	BEGIN_DATA_IO( TFileBlockDPool )
		DATA_IO_DEFN_FIXD( _TYPE, TFileBlockDPool, int, nDataType ),
		DATA_IO_DEFN_FIXD( _SIZE, TFileBlockDPool, int, nBulkSize ),
		DATA_IO_LAST();
	END_DATA_IO();
};

CBFBaseFileBlockDPool::CBFBaseFileBlockDPool(void)
	: m_uiDataType( DATATYPE_UNKNOWN )
{
	m_mBulkData.clear();
}

CBFBaseFileBlockDPool::~CBFBaseFileBlockDPool(void)
{
	auto itrErase = m_mBulkData.begin();
	while( itrErase != m_mBulkData.end() )
	{
		_SAFE_DELETE( itrErase->second );
		itrErase++;
	}
}

BOOL CBFBaseFileBlockDPool::Read(CBFDocBase* pDoc, CBFBaseFileIO* pFileIO)
{
	std::map< CString, TFileBulkData* > mBulkData;
	for( long indx=0; indx<m_header.nValue; ++indx )
	{
		TFileBulkData* pBulk = new TFileBulkData;
		pFileIO->ReadBlockData( *pBulk );

		mBulkData[ pBulk->strName ] = pBulk;
	}

	TFileBulkIO tBlock;
	TFileBlockDPool tData;

	// 2. File
	auto pBlockIO = TFileBlockDPool::GetDataIO();
	if( !MakeFileBlock( pBlockIO, &tBlock ) ) 
		return FALSE;

	// 3. Data to File
	LPVOID pData = &tData;
	auto itr = tBlock.vData.begin();
	while( itr != tBlock.vData.end() )
	{
		if( mBulkData.find( (*itr)->strName ) != mBulkData.end() )
		{
			memcpy( ((BYTE*)(pData)+(*itr)->ulOffset), 
				mBulkData[ (*itr)->strName ]->pBuffer,
				(*itr)->ulSize );
		}

		itr++;
	}

	auto itrErase = mBulkData.begin();
	while( itrErase != mBulkData.end() )
	{
		_SAFE_DELETE( itrErase->second );
		itrErase++;
	}

	m_uiDataType = tData.nDataType;

	//////////////////////////////////////////////////////////////////////////

	for( long indx=0; indx<tData.nBulkSize; ++indx )
	{
		TFileBulkData* pBulk = new TFileBulkData;
		pFileIO->ReadBlockData( *pBulk );

		m_mBulkData[ pBulk->strName ] = pBulk;
	}

	return TRUE;
}

BOOL CBFBaseFileBlockDPool::Write(CBFDocBase* pDoc, CBFBaseFileIO* pFileIO)
{
	auto pDBSession = pDoc->GetDBSession();

	long lCount = pDBSession->GetCount();
	for( long indx=0; indx<lCount; ++indx )
	{
		auto pDPoolBase = pDBSession->GetDataPoolBySeq(indx);
		if( pDPoolBase == nullptr ) { ASSERT(0); continue; }

		TFileBlockHeader tHeader;
		TFileBulkIO tBlock, tBlockData;

		// 1. File
		auto pDataIO = pDPoolBase->GetDataIO();
		MakeFileBlock( pDataIO, &tBlockData );

		// 2. Data to File
		TArrayITR taItr;
		long lSize = pDPoolBase->GetItrList(taItr);
		tBlockData.SetDataBufferSize( lSize );
		for(long indx=0; indx<lSize; ++indx )
		{
			auto pData = ITR_TO_DATABASE( taItr[indx] );
			for( auto pChildIO : tBlockData.vChild )
			{
				pChildIO->SetChildBufferSize( (BYTE*)pData );
			}
		}

		tBlockData.SetDataBufferSet();
		for(long indx=0; indx<lSize; ++indx )
		{
			auto pData = pDPoolBase->GetDefaultData( taItr[indx] );
			if( pData != nullptr ) 
				pData->IteratorToKey( pDBSession );

			tBlockData.SetDataBuffer( (BYTE*)pData );
			for( auto pChildIO : tBlockData.vChild )
			{
				pChildIO->SetChildBuffer( (BYTE*)pData );
			}
		}

		//////////////////////////////////////////////////////////////////////////

		// 1. Data
		TFileBlockDPool tData;
		tData.nDataType = pDPoolBase->GetDataType();
		tData.nBulkSize = tBlockData.ulBulkNum;

		// 2. File
		auto pBlockIO = TFileBlockDPool::GetDataIO();
		if( !MakeFileBlock( pBlockIO, &tBlock ) ) 
			return FALSE;

		// 3. Data to File
		auto pData = &tData;
		tBlock.SetDataBufferSize( 1 );
		tBlock.SetDataBufferSet();
		tBlock.SetDataBuffer( (BYTE*)pData );

		// 4. Header
		tHeader.nID = F_BLOCK_TYPE_DPOOL;
		tHeader.nValue = tBlock.ulBulkNum;

		pFileIO->WriteBlockHeader( tHeader );
		pFileIO->WriteBlockData( tBlock );
		pFileIO->WriteBlockData( tBlockData );
	}

	return TRUE;
}

BOOL CBFBaseFileBlockDPool::Stream(CBFDocBase* pDoc, CBFBaseFileIO* pFileIO)
{
	auto pDBSession = pDoc->GetDBSession();
	auto pDPoolBase = pDBSession->GetDataPool( m_uiDataType );

	TFileBulkIO tBlock;

	auto pDataIO = pDPoolBase->GetDataIO();
	MakeFileBlock( pDataIO, &tBlock );

	tBlock.SetDataStreamIO( m_mBulkData );
	tBlock.SetChildStreamIO( m_mBulkData );

	//////////////////////////////////////////////////////////////////////////

	if( tBlock.vData.empty() ) return FALSE;

	auto pData = pDPoolBase->GetDefaultData();

	ASSERT( tBlock.vData[0]->strName.CompareNoCase(_T("_KEY")) == 0 );
	long lDataSize = tBlock.vData[0]->ulBuffSize / tBlock.vData[0]->ulSize;
	for( long ldata=0; ldata<lDataSize; ++ldata )
	{
		pData->Init();
		tBlock.SetDataStream( (BYTE*)pData );
		tBlock.SetChildStream( (BYTE*)pData );

		if( pData != nullptr ) 
			pData->KeyToIterator( pDBSession );

		auto itr = pDPoolBase->InsertNU( pData );
		ASSERT( ITR_IS_VALID(itr) );
	}

	return TRUE;
}
