#pragma once

#include "..\MYENG_BASE\MYDialog.h"

class CExampleDlg : public CMYDialog
{
public:
	CExampleDlg(CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CExampleDlg();

	enum { IDD = IDD_APPUI_EXAMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX) override;
	virtual BOOL OnInitDialog() override;

protected:
	void SetText();
	void SetControl();
	void ExampleDB();

protected:
	DECLARE_MESSAGE_MAP();

};