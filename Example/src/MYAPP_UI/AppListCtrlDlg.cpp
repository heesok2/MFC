#include "pch.h"
#include "Resource.h"
#include "AppListCtrlDlg.h"

CAppListCtrlDlg::CAppListCtrlDlg(CDocBase * pDoc, CWnd * pParent)
	: CExDialog(CAppListCtrlDlg::IDD, pDoc, pParent)
{
}

CAppListCtrlDlg::~CAppListCtrlDlg()
{
}

void CAppListCtrlDlg::DoDataExchange(CDataExchange * pDX)
{
	CExDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_APPUI_LIST, m_listctrl);
}

BEGIN_MESSAGE_MAP(CAppListCtrlDlg, CExDialog)

END_MESSAGE_MAP();

BOOL CAppListCtrlDlg::OnInitDialog()
{
	CExDialog::OnInitDialog();

	SetText();

	SetControl();

	return TRUE;
}

void CAppListCtrlDlg::SetText()
{
}

void CAppListCtrlDlg::SetControl()
{
}
