#include "stdafx.h"
#include "Resource.h"
#include "IDialogProvider.h"

#include "ExampleDlg.h"

IDialogProvider * IDialogProvider::Instance()
{
	static IDialogProvider inst;
	return &inst;
}

BOOL IDialogProvider::ReqDialog(CDocBase * pDoc)
{
	CExampleDlg* pDlg = new CExampleDlg(pDoc);
	if (pDlg->Create())
	{
		pDlg->ShowWindow(SW_SHOW);
		pDlg->SetActiveWindow();
	}
	else
	{
		ASSERT(g_warning);
		delete pDlg;
	}

	return TRUE;
}
