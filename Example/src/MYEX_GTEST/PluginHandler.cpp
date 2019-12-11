#include "stdafx.h"
#include "PluginHandler.h"
#include "GoogleTestHelper.h"

BOOL ReqService(LPCTSTR strArguments)
{
	CGoogleTestHelper helper(0, (CString)strArguments);
	return helper.Run();
}