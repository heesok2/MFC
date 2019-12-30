#include "pch.h"
#include "MYDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMYDialog::CMYDialog(CDocBase * pDoc)
	: CDialog()
	, m_pMyDoc(pDoc)
	, m_bModeless(TRUE)
{
}

CMYDialog::CMYDialog(UINT uiResID, CDocBase * pDoc, CWnd * pParent)
	: CDialog(uiResID, pParent)
	, m_pMyDoc(pDoc)
	, m_bModeless(TRUE)
{
}

CMYDialog::~CMYDialog()
{
}

INT_PTR CMYDialog::DoModal()
{
	m_bModeless = FALSE;

	return CDialog::DoModal();
}

void CMYDialog::OnOK()
{
	CDialog::OnOK();

	if (m_bModeless)
		CDialog::DestroyWindow();
}

void CMYDialog::OnCancel()
{
	CDialog::OnCancel();

	if (m_bModeless)
		CDialog::DestroyWindow();
}

void CMYDialog::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	if (m_bModeless)
		delete this;
}