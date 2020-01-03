#pragma once

class CDocBase;
class AFX_EXT_CLASS CMyDialog : public CDialog
{
public:
	CMyDialog(CDocBase* pDoc);
	CMyDialog(UINT uiResID, CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CMyDialog();

public:
	virtual INT_PTR DoModal();

protected:
	virtual void OnOK();
	virtual void OnCancel();
	virtual void PostNcDestroy();

protected:
	BOOL m_bModeless; // default true
	CDocBase* m_pMyDoc;

};