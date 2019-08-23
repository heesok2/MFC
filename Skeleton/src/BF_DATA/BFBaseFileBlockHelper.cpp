#include "stdafx.h"
#include "BFBaseFileBlockHelper.h"
#include "BFBaseFileBlock.h"
#include "BFBaseFileBlockInfo.h"
#include "BFBaseFileBlockDPool.h"

#include "..\BF_LIB\IBFProduct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseFileBlockHelper::CBFBaseFileBlockHelper(CBFDocBase* pDoc, CString strFilePath)
	: m_pMyDoc( pDoc ), m_strFilePath( strFilePath )
{

}

CBFBaseFileBlockHelper::~CBFBaseFileBlockHelper(void)
{
}

BOOL CBFBaseFileBlockHelper::Read()
{
	if( !m_FileIO.FileOpen(m_strFilePath, _T("rb")) ) 
		return FALSE;

	BOOL bSuccess = TRUE;
	TFileBlockHeader curFH, preFH;

	try
	{
		do 
		{
			if( !bSuccess ) throw;

			if( !m_FileIO.ReadBlockHeader(curFH) ) throw;

			auto pBlock = CBFBaseFileFactory::GetInstance().Create( F_BLOCK_VERSION, curFH.nID );
			if( pBlock == nullptr ) throw;

			pBlock->SetHader( curFH );
			if( !pBlock->Read(m_pMyDoc, &m_FileIO) ) bSuccess = FALSE;
			if( !pBlock->Stream(m_pMyDoc, &m_FileIO) ) bSuccess = FALSE;

			_SAFE_DELETE( pBlock );

			preFH = curFH;

		} while( curFH.nID != F_BLOCK_TYPE_EOF );
	}
	catch (...)
	{
		ASSERT(0); 
		bSuccess = FALSE;
	}

	m_FileIO.FileClose();

	return bSuccess;
}

BOOL CBFBaseFileBlockHelper::Write()
{
	if( !m_FileIO.FileOpen(m_strFilePath, _T("wb")) )
		return FALSE;

	try
	{
		VEC_BLOCK vBlock;
		SetFileWriteBlock( vBlock );

		for( auto uiType : vBlock )
		{
			auto pBlock = CBFBaseFileFactory::GetInstance().Create( F_BLOCK_VERSION, uiType );
			if( pBlock == nullptr ) continue;

			if( !pBlock->Write( m_pMyDoc, &m_FileIO ) )
			{
				ASSERT(0);
			}

			_SAFE_DELETE( pBlock );
		}
	}
	catch (...)
	{
	}	

	m_FileIO.FileClose();

	return TRUE;
}

void CBFBaseFileBlockHelper::SetFileWriteBlock(VEC_BLOCK& vBlock)
{
	vBlock.clear();
	vBlock.push_back( F_BLOCK_TYPE_INFO  );
	vBlock.push_back( F_BLOCK_TYPE_DPOOL );
	vBlock.push_back( F_BLOCK_TYPE_EOF   );
}