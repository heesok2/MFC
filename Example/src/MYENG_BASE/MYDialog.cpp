#include "pch.h"
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMyDialog::CMyDialog(CDocBase * pDoc)
	: CDialog()
	, m_pMyDoc(pDoc)
	, m_bModeless(TRUE)
{
}

CMyDialog::CMyDialog(UINT uiResID, CDocBase * pDoc, CWnd * pParent)
	: CDialog(uiResID, pParent)
	, m_pMyDoc(pDoc)
	, m_bModeless(TRUE)
{
}

CMyDialog::~CMyDialog()
{
}

INT_PTR CMyDialog::DoModal()
{
	m_bModeless = FALSE;

	return CDialog::DoModal();
}

void CMyDialog::OnOK()
{
	CDialog::OnOK();

	if (m_bModeless)
		CDialog::DestroyWindow();
}

void CMyDialog::OnCancel()
{
	CDialog::OnCancel();

	if (m_bModeless)
		CDialog::DestroyWindow();
}

void CMyDialog::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if (m_bModeless)
		delete this;
}