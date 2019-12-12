#include "stdafx.h"
#include "PluginHandler.h"
#include "GoogleTestHelper.h"

BOOL ReqService(LPCTSTR strArguments, LPVOID)
{
	CGoogleTestHelper helper(0, (CString)strArguments);
	helper.Run();

	return TRUE;
}