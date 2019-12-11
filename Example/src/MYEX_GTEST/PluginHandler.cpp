#include "stdafx.h"
#include "PluginHandler.h"
#include "GoogleTestHelper.h"


BOOL ReqService(LPCTSTR strArguments, LPVOID lpInitData)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CGoogleTestHelper helper(0, (CString)strArguments);
	helper.Run();

	return TRUE;
}