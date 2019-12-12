#include "pch.h"
#include "PluginHandler.h"
#include "IDialogProvider.h"

BOOL ReqService(LPCTSTR strArguments, LPVOID lpInitData)
{
	CDocBase* pDocBase = nullptr;
	if (lpInitData != nullptr)
		pDocBase = static_cast<CDocBase*>(lpInitData);

	return IDialogProvider::Instance()->ReqDialog(pDocBase);
}
