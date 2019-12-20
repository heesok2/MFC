#pragma once

#include "..\MYEX_BASE\ExDialog.h"

class CAppListCtrlDlg : public CExDialog
{
public:
	CAppListCtrlDlg(CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CAppListCtrlDlg();

	enum { IDD = IDD_APPUI_LISTCTRL_DLG };

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

