#include "pch.h"
#include "PluginHandler.h"
#include "PluginResManager.h"
#include "IDialogProvider.h"


BOOL ReqService(LPCTSTR, LPVOID)
{
	SWITCH_RESOURCE;

	return IDialogProvider::Instance()->ReqDialog();
}