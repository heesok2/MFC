#pragma once

#include "HeaderPre.h"

struct TFileBlockHeader;
struct TFileBulkIO;
struct TFileBulkData;
class __MY_EXT_CLASS__ CBFBaseFileIO
{
public:
	CBFBaseFileIO(void);
	virtual ~CBFBaseFileIO(void);

public:
	BOOL FileOpen( CString strPath, CString strMode );
	void FileClose();

public:
	BOOL ReadBlockHeader( TFileBlockHeader& header );
	void WriteBlockHeader( TFileBlockHeader& header );

	void ReadBlockData( TFileBulkData& bulk );
	void WriteBlockData( TFileBulkIO& bulkio );
	void WriteBlockData( TFileBulkData& bulk );
	void WriteBlockSize( CString strBlockIO, TArrayl& taSize );

protected:
	FILE* m_pFile;
};

#include "HeaderPost.h"