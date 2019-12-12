#include "pch.h"
#include "PluginHandler.h"
#include "IDialogProvider.h"

#include "..\MYEX_BASE\DocBase.h"
#include "..\MYEX_DB\ExDBSession.h"

#include "ExDataDlg.h"

BOOL ReqService(LPCTSTR, LPVOID lpInitData)
{
	CDocBase* pDocBase = nullptr;
	if (lpInitData != nullptr)
		pDocBase = static_cast<CDocBase*>(lpInitData);

	return IDialogProvider::Instance()->ReqDialog(pDocBase);
}

BOOL ReqDataBase(LPVOID lpDataBase)
{
	CDocBase* pDocBase = nullptr;
	if (lpDataBase != nullptr)
		pDocBase = static_cast<CDocBase*>(lpDataBase);

	auto pDBSession = pDocBase->GetDBSession();

	pDBSession->m_aData.push_back(std::shared_ptr<CExDataDlg>(new CExDataDlg));

	return TRUE;
}
