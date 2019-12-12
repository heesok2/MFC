#include "pch.h"
#include "PluginHandler.h"
#include "IDialogProvider.h"

#include "ExDataDlg.h"

BOOL ReqService(LPCTSTR, LPVOID)
{
	return IDialogProvider::Instance()->ReqDialog();
}