#pragma once

#include "..\MYENG_BASE\MyDialog.h"

class CExampleDlg : public CMyDialog
{
public:
	CExampleDlg(CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CExampleDlg();

	enum { IDD = IDD_MYAPPUI_EXAMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;
	virtual void OnOK();

protected:
	void SetText();
	void SetControl();
	void Example();
	BOOL Execute();
	void ExecuteFace();
	void ExecuteBox();

protected:
	afx_msg void OnClickedApply();

	DECLARE_MESSAGE_MAP();

protected:
	CComboBox m_cobx;

};