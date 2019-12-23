#include "pch.h"
#include "PluginHandler.h"
#include "PluginResManager.h"
#include "IDialogProvider.h"

#include "ExDataDlg.h"

BOOL ReqService(LPCTSTR, LPVOID)
{
	SWITCH_RESOURCE;

	//auto pApp = AfxGetApp();
	//if (pApp == nullptr)
	//	return FALSE;

	//auto pos = pApp->GetFirstDocTemplatePosition();
	//auto pDocTemp = pApp->GetNextDocTemplate(pos);
	//if (pDocTemp == nullptr)
	//	return FALSE;

	//auto pDocPos = pDocTemp->GetFirstDocPosition();
	//auto pDoc = pDocTemp->GetNextDoc(pDocPos);

	return IDialogProvider::Instance()->ReqDialog();
}