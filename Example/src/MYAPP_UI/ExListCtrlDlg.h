#pragma once

#include "..\MYEX_BASE\ExDialog.h"

class CExListCtrlDlg : public CExDialog
{
public:
	CExListCtrlDlg(CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CExListCtrlDlg();

	enum { IDD = IDD_APPUI_EXAMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;

protected:
	void SetText();
	void SetControl();

protected:
	DECLARE_MESSAGE_MAP();

protected:
	CListCtrl m_listctrl;

};

