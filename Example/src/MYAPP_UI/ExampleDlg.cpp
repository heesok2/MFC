#include "pch.h"
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

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)

END_MESSAGE_MAP();

BOOL CExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetText();

	SetControl();

	return TRUE;
}

void CExampleDlg::SetText()
{
}

void CExampleDlg::SetControl()
{
}
