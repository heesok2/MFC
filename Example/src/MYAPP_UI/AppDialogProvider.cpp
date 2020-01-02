#include "pch.h"
#include "Resource.h"
#include "AppDialogProvider.h"

#include "ExampleDlg.h"
#include "AppListCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

	if (_tcscmp(lpDialogName, _T("CExampleDlg")) == 0)
	{
		CExampleDlg dlg(pDoc);
		if (lpParam != nullptr)
		{
			// Unknown
		}

		return dlg.DoModal();
	}
	else if (_tcscmp(lpDialogName, _T("CAppListCtrlDlg")) == 0)
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
