#include "pch.h"
#include "Resource.h"
#include "IDialogProvider.h"

#include "ExampleDlg.h"

IDialogProvider * IDialogProvider::Instance()
{
	static IDialogProvider inst;
	return &inst;
}

BOOL IDialogProvider::ReqDialog()
{
	CExampleDlg* pDlg = new CExampleDlg();
	if (pDlg->Create())
	{
		pDlg->ShowWindow(SW_SHOW);
		pDlg->SetActiveWindow();
	}
	else
	{
		ASSERT(0);
		delete pDlg;
	}

	return TRUE;
}
