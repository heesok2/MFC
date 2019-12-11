#include "pch.h"
#include "ExDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExDialog::CExDialog(CDocBase * pDoc)
	: CDialog()
	, m_pMyDoc(pDoc)
	, m_bModeless(TRUE)
{
}

CExDialog::CExDialog(UINT uiResID, CDocBase * pDoc, CWnd * pParent)
	: CDialog(uiResID, pParent)
	, m_pMyDoc(pDoc)
	, m_bModeless(TRUE)
{
}

CExDialog::~CExDialog()
{
}

INT_PTR CExDialog::DoModal()
{
	m_bModeless = FALSE;

	return CDialog::DoModal();
}

void CExDialog::OnOK()
{
	CDialog::OnOK();

	if (m_bModeless)
		CDialog::DestroyWindow();
}

void CExDialog::OnCancel()
{
	CDialog::OnCancel();

	if (m_bModeless)
		CDialog::DestroyWindow();
}

void CExDialog::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if (m_bModeless)
		delete this;
}