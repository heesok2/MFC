#include "stdafx.h"
#include "BFBaseFileBlockInfo.h"

#include "..\BF_LIB\BFBaseFileIO.h"
#include "..\BF_LIB\IBFProduct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BF_FILE_BLOCK_IMPL( F_BLOCK_VER_100, F_BLOCK_TYPE_INFO, CBFBaseFileBlockInfo );

struct TFileBlockInfo
{
	int nVersion;
	int nBuildNo;

	BEGIN_DATA_IO( TFileBlockInfo )
		DATA_IO_DEFN_FIXD( _VER, TFileBlockInfo, int, nVersion ),
		DATA_IO_DEFN_FIXD( _NO, TFileBlockInfo, int, nBuildNo ),
		DATA_IO_LAST();
	END_DATA_IO();
};

CBFBaseFileBlockInfo::CBFBaseFileBlockInfo(void)
{
	m_mBulkData.clear();
}

CBFBaseFileBlockInfo::~CBFBaseFileBlockInfo(void)
{
	auto itr = m_mBulkData.begin();
	while( itr != m_mBulkData.end() )
	{
		_SAFE_DELETE( itr->second );
		itr++;
	}
}

BOOL CBFBaseFileBlockInfo::Read(CBFDocBase* pDoc, CBFBaseFileIO* pFileIO)
{
	for( long indx=0; indx<m_header.nValue; ++indx )
	{
		TFileBulkData* pBulk = new TFileBulkData;
		pFileIO->ReadBlockData( *pBulk );

		m_mBulkData[ pBulk->strName ] = pBulk;
	}

	return TRUE;
}

BOOL CBFBaseFileBlockInfo::Write(CBFDocBase* pDoc, CBFBaseFileIO* pFileIO)
{
	TFileBlockHeader tHeader;
	TFileBulkIO tBlock;

	{
		// 1. Data
		TFileBlockInfo tData;
		tData.nVersion = IBFProduct::GetInstance()->GetProductVersion();
		tData.nBuildNo = IBFProduct::GetInstance()->GetProductBuildNo();

		// 2. File
		auto pDataIO = TFileBlockInfo::GetDataIO();
		if( !MakeFileBlock( pDataIO, &tBlock ) ) 
			return FALSE;

		// 3. Data to File
		auto pData = &tData;
		tBlock.SetDataBufferSize( 1 );
		tBlock.SetDataBufferSet();
		tBlock.SetDataBuffer( (BYTE*)pData );

		// 4. Header
		tHeader.nID = F_BLOCK_TYPE_INFO;
		tHeader.nValue = tBlock.ulBulkNum;
	}

	pFileIO->WriteBlockHeader( tHeader );
	pFileIO->WriteBlockData( tBlock );

	return TRUE;
}