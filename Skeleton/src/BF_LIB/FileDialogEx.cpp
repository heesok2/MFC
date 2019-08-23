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

// 굳이 필요하다면 사용하지만 CCmdTarget소멸자에서 ASSERTION생김(무시해도 됨)
void CFileDialogEx::SetButtonText(const CString& sButton) 
{ 
	m_sButton = sButton; 
	if(!m_sButton.IsEmpty()) 
		m_bVistaStyle = FALSE; // OnInitDialog()호출시키기 위함.
}

// Vista 이상에서는 호출안되서, m_bVistaStyle=FALSE 해야 들어옴(대화상자 안이쁨..쩝) 
BOOL CFileDialogEx::OnInitDialog()	
{
	CDialog::OnInitDialog();  

	if(!m_sButton.IsEmpty())
	{
		SetControlText(IDOK, m_sButton);
	}

	return TRUE; 
}
