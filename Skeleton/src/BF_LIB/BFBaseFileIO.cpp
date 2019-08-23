#include "stdafx.h"
#include "BFBaseFileIO.h"
#include "BFBaseFileDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseFileIO::CBFBaseFileIO(void) : m_pFile(nullptr)
{
}

CBFBaseFileIO::~CBFBaseFileIO(void)
{
}

BOOL CBFBaseFileIO::FileOpen(CString strPath, CString strMode)
{
	errno_t err = _tfopen_s( &m_pFile, strPath, strMode );
	if( err == EACCES || err != 0 ) 
	{
		// err == EACCES
		// Permmision Denied : 주로 윈도우 Vista 이상 계열에서 발생
		// 1. 네트워크 공유 파일에 권한이 없는 경우 (단순 쓰기 공유 옵션으로는 안됨)
		// 2. 관리자 권한 없이 C:\, C:\Windows\ 등 시스템 폴더에 접근한 경우

		return FALSE;
	}

	return TRUE;
}

void CBFBaseFileIO::FileClose()
{
	if( m_pFile )
		fclose( m_pFile );

	m_pFile = nullptr;
}

BOOL CBFBaseFileIO::ReadBlockHeader( TFileBlockHeader& header )
{
	return fread( &header, sizeof(TFileBlockHeader), 1, m_pFile ) > 0;
}

void CBFBaseFileIO::WriteBlockHeader( TFileBlockHeader& header )
{
	fwrite( &header, sizeof(header), 1, m_pFile );
}

void CBFBaseFileIO::ReadBlockData(TFileBulkData& bulk)
{
	// Bulk Keyword
	ULONG ulKeyword = 0;
	fread( &ulKeyword, sizeof(ULONG), 1, m_pFile );
	if( ulKeyword == 0 ) return;

	ulKeyword = ulKeyword / sizeof(TCHAR);
	auto pKeyword = new TCHAR[ ulKeyword+1 ];
	memset( pKeyword, 0, sizeof(TCHAR)*(ulKeyword+1) );
	fread( pKeyword, sizeof(TCHAR), ulKeyword, m_pFile );
	bulk.strName = pKeyword;
	_SAFE_DELETE_ARRAY( pKeyword );

	ULONG ulBufferSize = 0;
	fread( &ulBufferSize, sizeof(ulBufferSize), 1, m_pFile );
	if( ulBufferSize == 0 ) return;

	bulk.SetBuffer( ulBufferSize );
	fread( bulk.pBuffer, sizeof(unsigned char), bulk.ulBuffSize, m_pFile );
}

void CBFBaseFileIO::WriteBlockData(TFileBulkIO& bulkio)
{
	for( auto pBulkData : bulkio.vData )
	{
		WriteBlockData( *pBulkData );
	}

	for( auto pBlockData : bulkio.vChild )
	{
		WriteBlockSize( pBlockData->strBulk, pBlockData->taVariable );
		for( auto pSubBulkData : pBlockData->vData )
		{
			WriteBlockData( *pSubBulkData );
		}

		for( auto pSubBlockData : pBlockData->vChild )
		{
			WriteBlockSize( pSubBlockData->strBulk, pSubBlockData->taVariable );
			WriteBlockData( *pSubBlockData );
		}
	}
}

void CBFBaseFileIO::WriteBlockData(TFileBulkData& bulk)
{
	ULONG ulLength = bulk.strName.GetLength();
	ULONG ulKeyword = sizeof(TCHAR) * ulLength;

	// Bulk Keyword
	fwrite( &ulKeyword, sizeof(ULONG), 1, m_pFile );
	fwrite( (LPCTSTR)bulk.strName, sizeof(TCHAR), ulLength, m_pFile );

	// Bulk Data
	fwrite( &bulk.ulBuffSize, sizeof(bulk.ulBuffSize), 1, m_pFile );
	if( bulk.ulBuffSize > 0 ) 
		fwrite( bulk.pBuffer, sizeof(unsigned char), bulk.ulBuffSize, m_pFile );
}

void CBFBaseFileIO::WriteBlockSize(CString strBlockIO, TArrayl& taSize)
{
	ULONG ulLength = strBlockIO.GetLength();
	ULONG ulKeyword = sizeof(TCHAR) * ulLength;

	// Bulk Keyword
	fwrite( &ulKeyword, sizeof(ULONG), 1, m_pFile );
	fwrite( (LPCTSTR)strBlockIO, sizeof(TCHAR), ulLength, m_pFile );

	// Bulk Data
	ULONG ulBuffSize = sizeof(long)*taSize.GetSize();
	fwrite( &ulBuffSize, sizeof(ulBuffSize), 1, m_pFile );

	if( ulBuffSize > 0 ) 
		fwrite( taSize.GetData(), sizeof(long), taSize.GetSize(), m_pFile );
}