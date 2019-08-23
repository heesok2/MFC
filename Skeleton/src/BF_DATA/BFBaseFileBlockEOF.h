#pragma once

#include "BFBaseFileBlock.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CBFBaseFileBlockEOF : public CBFBaseFileBlock
{
	BF_FILE_BLOCK_DECLARE();

public:
	CBFBaseFileBlockEOF(void);
	virtual ~CBFBaseFileBlockEOF(void);

public:
	virtual BOOL Read( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );
	virtual BOOL Write( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );

private:
	std::map< CString, TFileBulkData* > m_mBulkData;

};

#include "HeaderPost.h"