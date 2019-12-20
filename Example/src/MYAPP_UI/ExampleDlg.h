#pragma once

#include "..\MYEX_BASE\ExDialog.h"

class CExampleDlg : public CExDialog
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

protected:
	DECLARE_MESSAGE_MAP();

};