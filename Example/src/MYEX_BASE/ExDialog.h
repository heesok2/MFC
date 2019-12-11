#pragma once

#include "ExtStart.h"

class CDocBase;
class __MY_EXT_CLASS__ CExDialog : public CDialog
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

#include "ExtFinish.h"
