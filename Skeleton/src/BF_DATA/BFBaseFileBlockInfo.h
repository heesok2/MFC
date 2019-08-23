#pragma once

#include "BFBaseFileBlock.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CBFBaseFileBlockInfo : public CBFBaseFileBlock
{
	BF_FILE_BLOCK_DECLARE();

public:
	CBFBaseFileBlockInfo(void);
	virtual ~CBFBaseFileBlockInfo(void);

public:
	virtual BOOL Read( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );
	virtual BOOL Write( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );

public:
	void WriteHeader();
	void WriteData();

private:
	std::map< CString, TFileBulkData* > m_mBulkData;

};

#include "HeaderPost.h"