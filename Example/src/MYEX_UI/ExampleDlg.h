#pragma once

class AFX_EXT_CLASS CExampleDlg : public CDialog
{
public:
	CExampleDlg(CWnd* pParent = nullptr);
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