#pragma once

#include <map>
#include <vector>

#include "..\BF_LIB\BFBaseFileDef.h"
#include "..\BF_LIB\BFBaseDataIO.h"

#include "BFBaseFileBlockDef.h"
#include "HeaderPre.h"

class CBFDocBase;
class CBFBaseFileIO;
class __MY_EXT_CLASS__ CBFBaseFileBlock
{
public:
	CBFBaseFileBlock(void);
	virtual ~CBFBaseFileBlock(void);

public:
	virtual UINT GetType() { return F_BLOCK_TYPE_UNKNOWN; }
	virtual BOOL Read( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO ) = 0;
	virtual BOOL Write( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO ) = 0;
	virtual BOOL Stream( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO ) { return TRUE; }

public:
	const TFileBlockHeader& GetHeader() const { return m_header; }
	void SetHader( TFileBlockHeader& _header ) { m_header = _header; }

protected:
	BOOL MakeFileBlock( const DATA_IO* pDataIO, TFileBulkIO* pBlock );
	long MakeFileBulkFixed( const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize );
	long MakeFileBulkIterator( const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize );
	long MakeFileBulkStruct( const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize );
	long MakeFileBulkArray( const DATA_IO* pDataIO, TFileBulkIO* pBlock, CString strItemName, UINT ulOffset, UINT ulSize );

protected:
	TFileBlockHeader m_header;

};

class __MY_EXT_CLASS__ CBFBaseFileFactory
{
	typedef CBFBaseFileBlock* (*CallBackFileBlock)();	

	struct TFileBlock
	{
		UINT uiVer;
		CallBackFileBlock fpFileBlock;

		TFileBlock( UINT _ver, CallBackFileBlock _fp ) 
			: uiVer(_ver), fpFileBlock(_fp) {}
	};

	typedef std::vector< TFileBlock > VEC_FILEBLOCK;
	typedef std::map< UINT, VEC_FILEBLOCK > MAP_FILEBLOCK;

public:
	static CBFBaseFileFactory& GetInstance();

public:
	CBFBaseFileFactory(void);
	virtual ~CBFBaseFileFactory(void);

public:
	CBFBaseFileBlock* Create( UINT uiVer, UINT uiType );

	BOOL Register( UINT uiVer, UINT uiType, CallBackFileBlock fpFileBlock );
	BOOL UnRegister( UINT uiVer, UINT uiType );	

protected:
	MAP_FILEBLOCK m_mFileBlock;

};

#include "HeaderPost.h"

#define BF_FILE_BLOCK_DECLARE()\
	public: virtual UINT GetType();

#define BF_FILE_BLOCK_IMPL( file_ver, type_id, class_name )\
	CBFBaseFileBlock* Create##class_name() { return ( new class_name ); }\
	BOOL bReg##class_name = CBFBaseFileFactory::GetInstance().Register( file_ver, type_id, Create##class_name );\
	UINT class_name::GetType() { return type_id; }