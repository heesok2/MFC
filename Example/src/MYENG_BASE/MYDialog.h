#pragma once

class CDocBase;
class AFX_EXT_CLASS CMYDialog : public CDialog
{
public:
	CMYDialog(CDocBase* pDoc);
	CMYDialog(UINT uiResID, CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CMYDialog();

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