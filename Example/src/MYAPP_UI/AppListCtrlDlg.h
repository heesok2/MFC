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
	void SetListHeader();
	long GetHeaderCheck();
	void SetHeaderCheck(BOOL bCheck);
	void SetListItem();

protected:
	afx_msg void OnNMClickAppuiList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkAppuiList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickAppuiList(NMHDR *pNMHDR, LRESULT *pResult);

	DECLARE_MESSAGE_MAP();

protected:
	CImageList m_aImage;
	CListCtrl m_listctrl;

};