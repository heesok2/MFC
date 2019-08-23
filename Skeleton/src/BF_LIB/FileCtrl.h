#pragma once

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CFileCtrl
{
public:
	CFileCtrl();
	CFileCtrl(LPCTSTR pszFilePathNameExt);        // "c:\midas\NXD\NXD.exe"
	virtual ~CFileCtrl();

public:
	void SetFilePathNameExt(LPCTSTR pszFilePathNameExt); // "c:\midas\NXD\NXD.exe"

	CString GetFilePathNameExt();                   // "c:\midas\NXD\NXD.exe"
	CString GetFilePathName();                      // "c:\midas\NXD\NXD"
	CString GetFilePath();                          // "c:\midas\NXD\"
	CString GetFileNameExt();                       // "NXD.exe"
	CString GetFileName();                          // "NXD"
	CString GetFileExt();                           // "exe"
	CString GetAbbPathNameExt(int nMaxLen);              // "c:\...\NXD.exe"
	CString GetAbbPathNameExt(CDC* pDC, LPRECT lpRect);  // "c:\...\NXD.exe"

	BOOL FileExists();
	BOOL GetFileStatus(CFileStatus& rFileStatus);
	static BOOL CopyFile(LPCTSTR lpszOldName, LPCTSTR lpszNewName);
	static BOOL FileExists(LPCTSTR pszFilePathNameExt);

	static size_t GetNumberOfFileLines( LPCTSTR pszFilePathNameExt );

protected:
	CString m_strFilePath;
	CString m_strFileName;
	CString m_strFileExt;
};
#include "HeaderPost.h"