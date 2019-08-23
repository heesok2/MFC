#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CFileDialogEx : public CFileDialog
{
public:
	CFileDialogEx(CDocument* pDoc, BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL,
		DWORD dwSize = 0,
		BOOL bVistaStyle = TRUE);
	virtual ~CFileDialogEx(void);

protected:
	virtual BOOL OnInitDialog();

public:
	void SetButtonText(const CString& sButton); // '열기/저장'버튼 텍스트 바꾸기

	// 혹시 Title Caption바꾸고 싶으면 
	// 인스턴스에서 m_ofn.lpstrTitle 접근하여 바꾸면 됨.

private:
	CString m_sInitPath;
	CString m_sButton;
};

#include "HeaderPost.h"
