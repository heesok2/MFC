#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ IBFProduct
{
	static IBFProduct* m_pInstance;

public:
	static IBFProduct* GetInstance() { return m_pInstance; } 

public:
	IBFProduct(void);
	virtual ~IBFProduct(void);

public:
	virtual CString GetProductName() = 0;
	virtual CString GetProductExt() = 0;
	virtual CString GetProductFilter() = 0;

	virtual UINT GetProgramCode() = 0;
	virtual UINT GetProductVersion() = 0;
	virtual UINT GetProductBuildNo() = 0;

};

#include "HeaderPost.h"