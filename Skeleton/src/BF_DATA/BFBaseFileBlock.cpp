#include "stdafx.h"
#include "BFBaseFileBlock.h"
#include "BFBaseFileBlockDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseFileBlock::CBFBaseFileBlock() 
{

}

CBFBaseFileBlock::~CBFBaseFileBlock(void)
{

}

BOOL CBFBaseFileBlock::MakeFileBlock(const DATA_IO* pDataIO, TFileBulkIO* pBlock)
{
	pBlock->InitData();

	long indx=0; 
	auto& lDataCount = pBlock->ulBulkNum;
	while( pDataIO[indx].uiDataType != DATA_IO_EMPTY )
	{
		switch ( pDataIO[indx].uiDataType )
		{
		case DATA_IO_FIXD: lDataCount += MakeFileBulkFixed( &pDataIO[indx], pBlock, pDataIO[indx].szName, pDataIO[indx].uiDataOffset, pDataIO[indx].uiDataSize ); break;
		case DATA_IO_ITER: lDataCount += MakeFileBulkIterator( &pDataIO[indx], pBlock, pDataIO[indx].szName, pDataIO[indx].uiDataOffset, pDataIO[indx].uiDataSize ); break;
		case DATA_IO_STRT: lDataCount += MakeFileBulkStruct( &pDataIO[indx], pBlock, pDataIO[indx].szName, pDataIO[indx].uiDataOffset, pDataIO[indx].uiDataSize ); break;
		case DATA_IO_ARRY: lDataCount += MakeFileBulkArray( &pDataIO[indx], pBlock, pDataIO[indx].szName, pDataIO[indx].uiDataOffset, pDataIO[indx].uiDataSize ); break;
		}

		indx++;
	}

	return lDataCount > 0;
}

long CBFBaseFileBlock::MakeFileBulkFixed(const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize)
{
	auto pItem = pBlock->AddData();
	pItem->strName = strItemName;
	pItem->eType = TFileBulkData::BULK_FIXD;
	pItem->ulOffset = ulOffset;
	pItem->ulSize = ulSize;

	return pItem != nullptr; // 1개
}

long CBFBaseFileBlock::MakeFileBulkIterator(const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize)
{
	auto pItem = pBlock->AddData();
	pItem->strName = strItemName;
	pItem->eType = TFileBulkData::BULK_ITER;
	pItem->ulOffset = ulOffset;
	pItem->ulSize = ulSize;

	return pItem != nullptr; // 1개
}

long CBFBaseFileBlock::MakeFileBulkStruct(const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize)
{
	long indx=0; 
	long lDataCount = 0;

	auto pSubDataIO = pDataIO->pStructIO;
	while( pSubDataIO[indx].uiDataType != DATA_IO_EMPTY )
	{
		CString strSubName = strItemName + pSubDataIO[indx].szName;
		UINT ulSubOffset = ulOffset + pSubDataIO[indx].uiDataOffset;

		switch ( pSubDataIO[indx].uiDataType )
		{
		case DATA_IO_FIXD: lDataCount += MakeFileBulkFixed( &pSubDataIO[indx], pBlock, strSubName, ulSubOffset, pSubDataIO[indx].uiDataSize ); break;
		case DATA_IO_ITER: lDataCount += MakeFileBulkIterator( &pSubDataIO[indx], pBlock, strSubName, ulSubOffset, pSubDataIO[indx].uiDataSize ); break;
		case DATA_IO_STRT: lDataCount += MakeFileBulkStruct( &pSubDataIO[indx], pBlock, strSubName, ulSubOffset, pSubDataIO[indx].uiDataSize ); break;
		case DATA_IO_ARRY: lDataCount += MakeFileBulkArray( &pSubDataIO[indx], pBlock, strSubName, ulSubOffset, pSubDataIO[indx].uiDataSize ); break;
		}

		indx++;
	}

	return lDataCount;
}

long CBFBaseFileBlock::MakeFileBulkArray(const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize)
{
	long lDataCount = 1; // Size Block 추가

	auto pChild = pBlock->AddChild();
	pChild->strBulk = strItemName + _T("//");
	pChild->ulOffset = ulOffset;
	pChild->ulSize = pDataIO->uiArrSize;
	pChild->pParent = pBlock;

	switch ( pDataIO->uiArrType )
	{
	case DATA_IO_FIXD: lDataCount += MakeFileBulkFixed( pDataIO, pChild, strItemName, 0, pDataIO->uiArrSize ); break;
	case DATA_IO_ITER: lDataCount += MakeFileBulkIterator( pDataIO, pChild, strItemName, 0, pDataIO->uiArrSize ); break;
	case DATA_IO_STRT: lDataCount += MakeFileBulkStruct( pDataIO, pChild, strItemName, 0, pDataIO->uiArrSize ); break;
	case DATA_IO_ARRY: lDataCount += MakeFileBulkArray( pDataIO, pChild, strItemName, 0, pDataIO->uiArrSize ); break;
	}
	
	return lDataCount;
}

CBFBaseFileFactory& CBFBaseFileFactory::GetInstance()
{
	static CBFBaseFileFactory _instance;
	return _instance;
}

CBFBaseFileFactory::CBFBaseFileFactory(void)
{
}

CBFBaseFileFactory::~CBFBaseFileFactory(void)
{
}

CBFBaseFileBlock* CBFBaseFileFactory::Create(UINT uiVer, UINT uiType)
{
	ASSERT( m_mFileBlock.find(uiType) != m_mFileBlock.end() );

	auto pFileBlock = static_cast<CBFBaseFileBlock*>( nullptr );

	auto lSize = static_cast<long>( m_mFileBlock[ uiType ].size() );
	for( long indx=0; indx<lSize; ++indx )
	{
		auto& tData = m_mFileBlock[ uiType ][ indx ];
		if( tData.uiVer & uiVer ) 
			pFileBlock = tData.fpFileBlock();
	}

	return pFileBlock;
}

BOOL CBFBaseFileFactory::Register(UINT uiVer, UINT uiType, CallBackFileBlock fpFileBlock)
{
	ASSERT( m_mFileBlock.find(uiType) == m_mFileBlock.end() );

	m_mFileBlock[ uiType ].push_back( std::move(TFileBlock(uiVer, fpFileBlock)) );

	return TRUE;
}

BOOL CBFBaseFileFactory::UnRegister(UINT uiVer, UINT uiType)
{
	auto itrType = m_mFileBlock.find( uiType );
	if( itrType != m_mFileBlock.end() )
	{
		auto lSize = static_cast<long>( itrType->second.size() );
		for( long indx=lSize-1; indx>=0; --indx )
		{
			auto& tData = itrType->second[ indx ];
			tData.uiVer &= !uiVer;

			if( tData.uiVer == F_BLOCK_VER_UNKNOWN ) 
			{
				auto itrDel = itrType->second.begin();
				itrType->second.erase( (itrDel+indx) );
			}
		}
	}

	return TRUE;
}