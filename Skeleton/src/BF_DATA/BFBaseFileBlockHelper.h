#pragma once

#include "..\BF_LIB\BFBaseFileIO.h"

#include <vector>
#include "HeaderPre.h"

class CBFDocBase;
class CBFBaseFileBlock;
class __MY_EXT_CLASS__ CBFBaseFileBlockHelper
{
	typedef std::vector<UINT> VEC_BLOCK;

public:
	CBFBaseFileBlockHelper( CBFDocBase* pDoc, CString strFilePath );
	virtual ~CBFBaseFileBlockHelper(void);

public:
	BOOL Read();
	BOOL Write();
	
protected:
	void SetFileWriteBlock( VEC_BLOCK& vBlock );

protected:
	CBFDocBase* m_pMyDoc;

	CString m_strFilePath;
	CBFBaseFileIO m_FileIO;
};

#include "HeaderPost.h"