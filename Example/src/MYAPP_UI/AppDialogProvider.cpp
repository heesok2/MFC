#include "pch.h"
#include "Resource.h"
#include "AppDialogProvider.h"

CAppDialogProvider::CAppDialogProvider()
{
}

CAppDialogProvider::~CAppDialogProvider()
{
}

INT_PTR CAppDialogProvider::DoModal(CDocBase * pDoc, LPCTSTR lpDialogName, LPVOID lpParam)
{
	if (lpDialogName == _T("CExampleDlg"))
	{

	}

	ASSERT(g_warning);

	return 0;
}
