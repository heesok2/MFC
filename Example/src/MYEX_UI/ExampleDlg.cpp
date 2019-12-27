#include "pch.h"
#include "Resource.h"
#include "ExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExampleDlg::CExampleDlg(CWnd * pParent)
	: CMYDialog(CExampleDlg::IDD, nullptr, pParent)
{
}

CExampleDlg::~CExampleDlg()
{
}

void CExampleDlg::DoDataExchange(CDataExchange * pDX)
{
	CMYDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExampleDlg, CMYDialog)

END_MESSAGE_MAP();

BOOL CExampleDlg::OnInitDialog()
{
	CMYDialog::OnInitDialog();


	return TRUE;
}

BOOL CExampleDlg::Create(CWnd * pParent)
{
	return CMYDialog::Create(CExampleDlg::IDD, pParent);
}