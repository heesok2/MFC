#include "stdafx.h"
#include "BFPProductImpl.h"
#include "BFProductDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFPProductImpl _g_instance;

CBFPProductImpl::CBFPProductImpl(void)
{
}

CBFPProductImpl::~CBFPProductImpl(void)
{
}

CString CBFPProductImpl::GetProductName()
{
	return D_PRODUCT_NAME;
}

CString CBFPProductImpl::GetProductExt()
{
	return D_MODEL_FILE_EXT;
}

CString CBFPProductImpl::GetProductFilter()
{
	return D_MODEL_FILE_FILTER;
}

UINT CBFPProductImpl::GetProgramCode()
{
	return D_PROG_BFP;
}

UINT CBFPProductImpl::GetProductVersion()
{
	return D_PRODUCT_VERSION;
}

UINT CBFPProductImpl::GetProductBuildNo()
{
	return D_PRODUCT_BUILD_NO;
}
