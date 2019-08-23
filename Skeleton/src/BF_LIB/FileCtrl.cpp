#include "stdafx.h"
#include "FileCtrl.h"

#include <string>
#include <fstream>

#include <afxtempl.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileCtrl::CFileCtrl()
{
	CString csNullFile;
	SetFilePathNameExt(csNullFile);
}

CFileCtrl::CFileCtrl(LPCTSTR pszFilePathNameExt)
{
	SetFilePathNameExt(pszFilePathNameExt);
}

CFileCtrl::~CFileCtrl()
{
}

void CFileCtrl::SetFilePathNameExt(LPCTSTR pszFilePathNameExt)
{
	CString csPathNameExt;  /* rstrFilePathAndName : c:\midas\gen.exe */
	m_strFilePath.Empty();  /* only path           : c:\midas\        */
	m_strFileName.Empty();  /* only file name      : gen              */
	m_strFileExt.Empty();   /* only extention      : exe              */

	csPathNameExt = pszFilePathNameExt;

	int nStrLength, nFindBackSlash;
	nStrLength=csPathNameExt.GetLength();
	nFindBackSlash=csPathNameExt.ReverseFind('\\');

	CString csFileNameExt;
	if(nFindBackSlash != -1)
	{
		m_strFilePath = csPathNameExt.Left(nFindBackSlash+1);
		csFileNameExt = csPathNameExt.Mid(nFindBackSlash+1);
	}
	else csFileNameExt = csPathNameExt;

	int nFind=csFileNameExt.ReverseFind('.');
	if(nFind == -1)
	{
		m_strFileName = csFileNameExt;
		// m_strFileExt.Empty() // already initialized
	}
	else
	{
		m_strFileName = csFileNameExt.Left(nFind);
		m_strFileExt = csFileNameExt.Mid(nFind+1);
	}
}

CString CFileCtrl::GetFilePathNameExt()
{
	CString csName;
	csName += m_strFilePath + m_strFileName;
	if (!m_strFileExt.IsEmpty()) csName += _T(".")+m_strFileExt;
		return csName;
}

CString CFileCtrl::GetFilePathName()
{
	return m_strFilePath + m_strFileName;
}

CString CFileCtrl::GetFilePath()
{
	return m_strFilePath;
}

CString CFileCtrl::GetFileNameExt()
{
	CString csName;
	if (!m_strFileExt.IsEmpty()) csName = m_strFileName+_T(".")+m_strFileExt;
	else csName = m_strFileName;
		return csName;
}

CString CFileCtrl::GetFileName()
{
	return m_strFileName;
}

CString CFileCtrl::GetFileExt()
{
	return m_strFileExt;
}

CString CFileCtrl::GetAbbPathNameExt(int nMaxLen)
{
	CString csFile, csPathOnly, csFileNameExt;

	csFile = GetFilePathNameExt();
	csPathOnly = GetFilePath();
	csFileNameExt = GetFileNameExt();
	int nStart = 0;
	int nPos;
	CArray<int, int> aPos;  // Path에서 백 슬래쉬 위치 다 찾아내기
	while ((nPos = csPathOnly.Find('\\', nStart)) != -1)
	{
		aPos.Add(nPos);
		nStart = nPos+1;
	}
	int nBScount = static_cast<int>(aPos.GetSize());  // 백 슬래쉬 갯수
	int nRemove = 1;  // 제거할 백슬래쉬 위치 (두 번 째부터 제거된다.)

	CString csAbbPath = csPathOnly;
	while ((nRemove < nBScount) && csFile.GetLength() > nMaxLen)
	{
		// 중간 Path를 하나 제거한다.
		csAbbPath = csPathOnly.Left(aPos[0]+1)+_T("...")+csPathOnly.Mid(aPos[nRemove]);
		nRemove++;

		csFile = csAbbPath+csFileNameExt;
		if (csFile.GetLength() <= nMaxLen) return csFile;
	}
	if (csFile.GetLength() > nMaxLen) csFile = csFileNameExt;

	return csFile;
}

// pDC가 폰트를 Select한 후 호출되어야 한다. 
// Dialog의 경우 CClient dc(this); dc.SelectObject(GetFont());
CString CFileCtrl::GetAbbPathNameExt(CDC* pDC, LPRECT lpRect)
{
	CString csFile, csPathOnly, csFileNameExt;

	csFile = GetFilePathNameExt();
	csPathOnly = GetFilePath();
	csFileNameExt = GetFileNameExt();

	int nStart = 0;
	int nPos;
	CArray<int, int> aPos;  // Path에서 백 슬래쉬 위치 다 찾아내기
	while ((nPos = csPathOnly.Find('\\', nStart)) != -1)
	{
		aPos.Add(nPos);
		nStart = nPos+1;
	}
	int nBScount = static_cast<int>(aPos.GetSize());  // 백 슬래쉬 갯수
	int nRemove = 1;  // 제거할 백슬래쉬 위치 (두 번 째부터 제거된다.)

	CSize size;
	SIZE s;
	CRect r(lpRect);

	// Full Path 시도
	size = pDC->GetTextExtent(csFile);
	s.cx = size.cx;
	s.cy = size.cy;
	pDC->LPtoDP(&s);
	CString csAbbPath = csPathOnly;
	while ((nRemove < nBScount) && (s.cx > r.Width()))
	{
		// 중간 Path를 하나 제거한다.
		csAbbPath = csPathOnly.Left(aPos[0]+1)+_T("...")+csPathOnly.Mid(aPos[nRemove]);
		nRemove++;

		csFile = csAbbPath+csFileNameExt;
		size = pDC->GetTextExtent(csFile);
		s.cx = size.cx;
		s.cy = size.cy;
		pDC->LPtoDP(&s);
	}
	if (s.cx > r.Width())
		csFile = csFileNameExt;

	return csFile;
}

BOOL CFileCtrl::FileExists(LPCTSTR pszFilePathNameExt)
{
	CFileStatus FileStatus;
	return CFile::GetStatus(pszFilePathNameExt, FileStatus);
}

BOOL CFileCtrl::FileExists()
{
	CFileStatus FileStatus;
	return CFile::GetStatus(GetFilePathNameExt(), FileStatus);
}

BOOL CFileCtrl::GetFileStatus(CFileStatus& rFileStatus)
{
	return CFile::GetStatus(GetFilePathNameExt(), rFileStatus);
}

#pragma warning(disable:4996)
BOOL CFileCtrl::CopyFile(LPCTSTR lpszOldName, LPCTSTR lpszNewName)
{
	FILE *fold, *fnew;
	int c;
	if((fold = _tfopen(lpszOldName, _T("rb")))==NULL) return FALSE;

	if((fnew = _tfopen(lpszNewName, _T("wb")))==NULL)
	{
		fclose(fold);
		return FALSE;
	}

	while(TRUE)
	{
		c = fgetc(fold);
		if(!feof(fold)) fputc(c,fnew);
		else break;
	}

	fclose(fnew);
	fclose(fold);

	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// GetNumberOfFileLines
// 파일이 다른 File함수로 열려있지 않다는 가정하에 사용해야 함.
// binary 파일은 불가능함.
size_t CFileCtrl::GetNumberOfFileLines( LPCTSTR pszFilePathNameExt )
{
	CFileStatus FileStatus;
	if(!CFile::GetStatus(pszFilePathNameExt, FileStatus)) { ASSERT(0); return 0; }

	std::ifstream  ChkFile(pszFilePathNameExt, std::ifstream::in);
	if(!ChkFile.is_open()) return 0;

	std::string line;
	size_t nLine=0;
	while(std::getline(ChkFile, line)) nLine++;

	ChkFile.close();
	return nLine;
}
