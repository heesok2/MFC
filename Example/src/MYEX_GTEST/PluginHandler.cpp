#include "stdafx.h"
#include "PluginHandler.h"
#include "PluginResManager.h"
#include "GoogleTestHelper.h"

BOOL ReqService(LPCTSTR strArguments, LPVOID)
{
	SWITCH_RESOURCE;

	CGoogleTestHelper helper(0, (CString)strArguments);
	return helper.Run();
}