#include "stdafx.h"
#include "Resource.h"
#include "ExampleDlg.h"

CExampleDlg::CExampleDlg(CDocBase * pDoc, CWnd * pParent)
	: CExDialog(CExampleDlg::IDD, pDoc, pParent)
{
}

CExampleDlg::~CExampleDlg()
{
}

void CExampleDlg::DoDataExchange(CDataExchange * pDX)
{
	CExDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExampleDlg, CExDialog)

END_MESSAGE_MAP();

BOOL CExampleDlg::OnInitDialog()
{
	CExDialog::OnInitDialog();


	return TRUE;
}

BOOL CExampleDlg::Create(CWnd * pParent)
{
	return CExDialog::Create(CExampleDlg::IDD, pParent);
}


