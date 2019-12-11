#pragma once

#include "..\MYEX_BASE\ExDialog.h"

class CExampleDlg : public CExDialog
{
public:
	CExampleDlg(CDocBase* pDoc, CWnd* pParent = nullptr);
	virtual ~CExampleDlg();

	enum { IDD = IDD_EXAMPLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

public:
	BOOL Create(CWnd* pParent = nullptr);


protected:
	DECLARE_MESSAGE_MAP();

};