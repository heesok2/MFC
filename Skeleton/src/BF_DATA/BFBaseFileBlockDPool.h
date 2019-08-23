#pragma once

#include "BFBaseFileBlock.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ CBFBaseFileBlockDPool : public CBFBaseFileBlock
{
	BF_FILE_BLOCK_DECLARE();

public:
	CBFBaseFileBlockDPool(void);
	virtual ~CBFBaseFileBlockDPool(void);

public:
	virtual BOOL Read( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );
	virtual BOOL Write( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );
	virtual BOOL Stream( CBFDocBase* pDoc, CBFBaseFileIO* pFileIO );

private:
	UINT m_uiDataType;
	std::map< CString, TFileBulkData* > m_mBulkData;

};

#include "HeaderPost.h"