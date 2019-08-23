#pragma once

#include <vector>
#include <map>

struct TFileBulkData
{
	enum BULK_TYPE { BULK_UNKNOWN = 0, BULK_FIXD, BULK_ITER };

	CString strName;
	BULK_TYPE eType;

	ULONG ulSize;
	ULONG ulOffset;

	ULONG ulVarIdx;
	ULONG ulVarNum;
	TArrayl taVariable;

	ULONG ulPosition;
	ULONG ulBuffSize;
	unsigned char* pBuffer;
	TArrayub taBuffer; // Read/Write Buffer 할당용

	TFileBulkData() :
		strName(_T("")), eType(BULK_UNKNOWN),
		ulSize(0), ulOffset(0),
		ulVarIdx(0), ulVarNum(0),
		ulPosition(0), ulBuffSize(0), pBuffer(nullptr)
	{ 
	}

	~TFileBulkData() 
	{ 
	}

	void SetBuffer( long lSize )
	{
		taBuffer.SetSize( lSize );

		ulBuffSize = lSize;
		pBuffer = taBuffer.GetData();
	}

	void ReadBuffer( BYTE* pDataBase )
	{
		if( ulBuffSize == 0 || pBuffer == nullptr )
			return;
		
		if( (ulPosition+ulSize) <= ulBuffSize )
			memcpy( pDataBase+ulOffset, pBuffer+ulPosition, ulSize );
		
		ulPosition += ulSize;
	}

	void WriteBuffer( BYTE* pDataBase )
	{
		if( ulBuffSize == 0 || pBuffer == nullptr )
			return;

		if( (ulPosition+ulSize) <= ulBuffSize )
			memcpy( pBuffer+ulPosition, pDataBase+ulOffset, ulSize );
	
		ulPosition += ulSize;
	}
};

struct TFileBulkIO
{
	typedef std::vector<TFileBulkIO*> vec_io;
	typedef std::vector<TFileBulkData*> vec_data;

	CString strBulk; // Bulk IO Name
	ULONG ulBulkNum; // Bulk Data Num ( Child 포함 )

	ULONG ulSize;	 // Data Size
	ULONG ulOffset;	 // Struct Offset 

	ULONG ulVarIdx;	 // Variable Index 
	ULONG ulVarNum;	 // Variable Num ( Array > Size 누적을 위해서 )
	TArrayl taVariable; 

	TFileBulkIO* pParent;
	vec_io vChild;
	vec_data vData;

	TFileBulkIO() :
		strBulk(_T("")), ulBulkNum(0),	// Bulk Infomation
		ulSize(0), ulOffset(0),			// Bulk Data
		ulVarIdx(0), ulVarNum(0),		// Bulk Variable
		pParent(nullptr)				// Bulk Child
	{}

	~TFileBulkIO()
	{
		InitData();
	}

	void InitData()
	{
		strBulk = _T("");
		ulBulkNum = 0;

		ulSize = 0;
		ulOffset = 0;		

		ulVarIdx = 0;
		ulVarNum = 0;
		taVariable.RemoveAll();

		pParent = nullptr;

		auto itrChild = vChild.begin();
		while( itrChild != vChild.end() ) 
		{ _SAFE_DELETE(*itrChild); itrChild++; }
		vChild.clear();

		auto itrItem = vData.begin();
		while( itrItem != vData.end() )
		{ _SAFE_DELETE(*itrItem); itrItem++; }
		vData.clear();
	}

	TFileBulkIO* AddChild() 
	{
		auto pChild = new TFileBulkIO;
		if( pChild ) vChild.push_back( pChild );
		return pChild; 
	}

	TFileBulkData* AddData() 
	{
		auto pItem = new TFileBulkData;
		if( pItem ) vData.push_back( pItem );
		return pItem; 
	}

#pragma region IO_READ

	void SetDataStreamIO( std::map<CString, TFileBulkData *>& m_mBulkData )
	{
		for( auto pBlock : vData )
		{
			if( m_mBulkData.find( pBlock->strName ) != m_mBulkData.end() )
			{
				pBlock->ulBuffSize = m_mBulkData[ pBlock->strName ]->ulBuffSize;
				pBlock->pBuffer = m_mBulkData[ pBlock->strName ]->pBuffer;
			}
		}
	}

	void SetChildStreamIO( std::map<CString, TFileBulkData *>& mBulkData )
	{
		for( auto pChild : vChild )
		{
			if( mBulkData.find( pChild->strBulk ) != mBulkData.end() )
				pChild->SetVariableStream( mBulkData[ pChild->strBulk ]->ulBuffSize, mBulkData[ pChild->strBulk ]->pBuffer );

			pChild->SetDataStreamIO( mBulkData );
			pChild->SetChildStreamIO( mBulkData );
		}
	}

	void SetVariableStream( ULONG ulBuffSize, unsigned char* pBuffer )
	{
		auto lDataSize = ulBuffSize / sizeof(long);
		if( lDataSize == 0 ) return;

		ulVarIdx = 0;
		ulVarNum = lDataSize;
		taVariable.SetSize( lDataSize );

		auto pVariable = taVariable.GetData();
		memcpy( pVariable, pBuffer, sizeof(long)*lDataSize );
	}

	void SetDataStream( BYTE* pDataBase )
	{
		for( auto pBlock : vData )
		{
			if( pBlock->pBuffer != nullptr )
				pBlock->ReadBuffer( pDataBase );
		}
	}

	void SetChildStream( BYTE* pDataBase )
	{
		for( auto pChild : vChild )
		{
			if( pChild->ulVarNum == 0 )continue;
			if( pChild->ulVarIdx >= pChild->ulVarNum ) continue;

			BYTE* pData = NULL;
			long lSize = 0;

 			if( pChild->taVariable[pChild->ulVarIdx] == 0 )
 			{
				pData = NULL;
				lSize = 0;
 			}
 			else
 			{
 				pData = (BYTE*)malloc( pChild->ulSize * pChild->taVariable[pChild->ulVarIdx] );
 				memset( pData, 0, pChild->ulSize * pChild->taVariable[pChild->ulVarIdx] );
 
 				lSize = pChild->taVariable[pChild->ulVarIdx];
 			}

			BYTE** ppData = (BYTE**)(pDataBase + pChild->ulOffset );
			long*  pSize  = (long*)(pDataBase + pChild->ulOffset + sizeof(LPVOID));
			if( (*ppData) != NULL ) free( (*ppData) );
			(*ppData) = pData;
			(*pSize) = lSize;

			if( pChild->taVariable[ pChild->ulVarIdx++ ] == 0 )
				continue;
 
 			for(long i=0; i< (*pSize ); i++)
 			{
 				pChild->SetDataStream( pData );
 				pChild->SetChildStream( pData );
 
 				pData = (BYTE*)( pData + pChild->ulSize );
 			}			
		}
	}

#pragma endregion

#pragma region IO_WRITE

	void SetDataBufferSet()
	{
		for( auto pBulkData : vData )
			pBulkData->SetBuffer( pBulkData->ulBuffSize );

		for( auto pChild : vChild )
			pChild->SetDataBufferSet();
	}

	void SetDataBufferSize( long lDataSize )
	{
		for( auto pBulkData : vData )
			pBulkData->ulBuffSize = lDataSize * pBulkData->ulSize;		
	}

	void SetChildBufferSize( BYTE* pDataBase )
	{
		ulVarNum++; // TArray > Size 0 이라도 추가

		auto lpData = *((BYTE**)(pDataBase + ulOffset));
		auto lDataSize = *((long*)(pDataBase + ulOffset + sizeof(LPVOID)));
		if( lDataSize == 0 ) return; 

		for( auto pBulkData : vData )
			pBulkData->ulBuffSize += lDataSize * pBulkData->ulSize;

		for( auto indx=0; indx<lDataSize; ++indx )
		{
			for( auto pChildIO : vChild )
				pChildIO->SetChildBufferSize( lpData );

			lpData = lpData + ulSize;
		}
	}

	void SetDataBuffer( BYTE* pDataBase )
	{
		for( auto pBulkData : vData )
			pBulkData->WriteBuffer( pDataBase );
	}

	void SetChildBuffer( BYTE* pDataBase )
	{
		if( ulVarNum == 0 ) return;

		auto lpData = *((BYTE**)(pDataBase + ulOffset));
		auto lDataSize = *((long*)(pDataBase + ulOffset + sizeof(LPVOID)));

		if( taVariable.IsEmpty() ) 
			taVariable.SetSize( ulVarNum );

		taVariable[ ulVarIdx++ ] = lDataSize;
		for( long indx=0; indx<lDataSize; ++indx )
		{
			for( auto pBulkItem : vData )
				pBulkItem->WriteBuffer( (BYTE*)lpData );

			for( auto pChildIO : vChild )
				pChildIO->SetChildBuffer( (BYTE*)lpData );

			lpData = lpData + ulSize;
		}
	}

#pragma endregion

};

struct TFileBlockHeader
{
	int nID;
	int nValue;

	TFileBlockHeader() : nID(0), nValue(0)
	{

	}
};