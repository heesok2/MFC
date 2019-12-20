#include "pch.h"
#include "Resource.h"
#include "AppDialogProvider.h"

#include "ExampleDlg.h"
#include "AppListCtrlDlg.h"

CAppDialogProvider::CAppDialogProvider()
{
}

CAppDialogProvider::~CAppDialogProvider()
{
}

INT_PTR CAppDialogProvider::DoModal(CDocBase * pDoc, LPCTSTR lpDialogName, LPVOID lpParam)
{
	if (pDoc == nullptr)
	{
		ASSERT(g_warning);
		return 0;
	}

	CWnd* pMainWnd = AfxGetMainWnd();

	CRect rcMain;
	pMainWnd->GetWindowRect(rcMain);

	if (wcscmp(lpDialogName, _T("CExampleDlg")) == 0)
	{
		
	}
	else if (wcscmp(lpDialogName, _T("CAppListCtrlDlg")) == 0)
	{
		CAppListCtrlDlg dlg(pDoc);
		if (lpParam != nullptr)
		{
			// Unknown
		}

		return dlg.DoModal();
	}

	ASSERT(g_warning);
	return 0;
}
