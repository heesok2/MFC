#include "pch.h"
#include "Resource.h"
#include "ExListCtrlDlg.h"

CExListCtrlDlg::CExListCtrlDlg(CDocBase * pDoc, CWnd * pParent)
	: CExDialog(CExListCtrlDlg::IDD, pDoc, pParent)
{
}

CExListCtrlDlg::~CExListCtrlDlg()
{
}

void CExListCtrlDlg::DoDataExchange(CDataExchange * pDX)
{
	CExDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_APPUI_LIST, m_listctrl);
}

BEGIN_MESSAGE_MAP(CExListCtrlDlg, CDialog)

END_MESSAGE_MAP();

BOOL CExListCtrlDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetText();

	SetControl();

	return TRUE;
}

void CExListCtrlDlg::SetText()
{
}

void CExListCtrlDlg::SetControl()
{
}
