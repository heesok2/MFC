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
	void SetButtonText(const CString& sButton); // '����/����'��ư �ؽ�Ʈ �ٲٱ�

	// Ȥ�� Title Caption�ٲٰ� ������ 
	// �ν��Ͻ����� m_ofn.lpstrTitle �����Ͽ� �ٲٸ� ��.

private:
	CString m_sInitPath;
	CString m_sButton;
};

#include "HeaderPost.h"
