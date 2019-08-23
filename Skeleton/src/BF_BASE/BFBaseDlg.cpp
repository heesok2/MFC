#include "stdafx.h"
#include "BFBaseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseDlg::CBFBaseDlg(void) : CDialog(CBFBaseDlg::IDD, NULL)
{
}

CBFBaseDlg::~CBFBaseDlg(void)
{
}

void CBFBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CBFBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}
