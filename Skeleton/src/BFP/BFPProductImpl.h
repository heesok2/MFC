#pragma once

#include "..\BF_LIB\IBFProduct.h"

class CBFPProductImpl : public IBFProduct
{
public:
	CBFPProductImpl(void);
	virtual ~CBFPProductImpl(void);

public:
	virtual CString GetProductName();
	virtual CString GetProductExt();
	virtual CString GetProductFilter();

	virtual UINT GetProgramCode();
	virtual UINT GetProductVersion();
	virtual UINT GetProductBuildNo();

};