#pragma once

class CDocBase;
class AFX_EXT_CLASS CExDialog : public CDialog
{
public:
	CExDialog(CDocBase* pDoc);
	CExDialog(UINT uiResID, CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CExDialog();

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