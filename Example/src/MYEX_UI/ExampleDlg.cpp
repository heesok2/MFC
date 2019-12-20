#include "..\MYAPP_UI\ExampleDlg.h"
#include "pch.h"
#include "Resource.h"
#include "ExampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExampleDlg::CExampleDlg(CWnd * pParent)
	: CDialog(CExampleDlg::IDD, pParent)
{
}

CExampleDlg::~CExampleDlg()
{
}

void CExampleDlg::DoDataExchange(CDataExchange * pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)

END_MESSAGE_MAP();

BOOL CExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE;
}

BOOL CExampleDlg::Create(CWnd * pParent)
{
	return CDialog::Create(CExampleDlg::IDD, pParent);
}