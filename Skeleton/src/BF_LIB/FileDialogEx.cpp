#include "StdAfx.h"
#include "FileDialogEx.h"
#include "FileCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFileDialogEx::CFileDialogEx(CDocument* pDoc, BOOL bOpenFileDialog, LPCTSTR lpszDefExt,LPCTSTR lpszFileName,
							 DWORD dwFlags, LPCTSTR lpszFilter,CWnd* pParentWnd,DWORD dwSize,BOOL bVistaStyle)
							 :CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd, dwSize, bVistaStyle)
{
	if(pDoc)
	{
		const CString& strCurDocName = pDoc->GetPathName();
		CFileCtrl fc;
		if(!strCurDocName.IsEmpty())
		{
			fc.SetFilePathNameExt((LPCTSTR)strCurDocName);	
			m_sInitPath = fc.GetFilePath();
			m_ofn.lpstrInitialDir = (LPCTSTR)(m_sInitPath);
		}
	}	
}

CFileDialogEx::~CFileDialogEx(void)
{
}

// ���� �ʿ��ϴٸ� ��������� CCmdTarget�Ҹ��ڿ��� ASSERTION����(�����ص� ��)
void CFileDialogEx::SetButtonText(const CString& sButton) 
{ 
	m_sButton = sButton; 
	if(!m_sButton.IsEmpty()) 
		m_bVistaStyle = FALSE; // OnInitDialog()ȣ���Ű�� ����.
}

// Vista �̻󿡼��� ȣ��ȵǼ�, m_bVistaStyle=FALSE �ؾ� ����(��ȭ���� ���̻�..��) 
BOOL CFileDialogEx::OnInitDialog()	
{
	CDialog::OnInitDialog();  

	if(!m_sButton.IsEmpty())
	{
		SetControlText(IDOK, m_sButton);
	}

	return TRUE; 
}
