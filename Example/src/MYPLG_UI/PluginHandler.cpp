#include "pch.h"
#include "PluginHandler.h"
#include "PluginResManager.h"

BOOL ReqService(LPCTSTR, LPVOID)
{
	SWITCH_RESOURCE;

	return TRUE;
}