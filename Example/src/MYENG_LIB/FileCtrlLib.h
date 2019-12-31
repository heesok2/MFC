#pragma once

namespace mylib
{
	class AFX_EXT_CLASS CFileCtrlLib
	{
	public:
		CFileCtrlLib();
		CFileCtrlLib(const CString& strFilePath);
		virtual ~CFileCtrlLib();

	public:
		void SetFilePath(const CString& strFilePath);
		BOOL Exist();
		CString GetPathNameExt();
		CString GetPathName();
		CString GetPath();
		CString GetName();
		CString GetExt();

	public:
		static BOOL Exist(const CString& strFullPath);
		static CString Absolute2Relative(const CString& src, const CString& trg);

	protected:
		CString m_strFullPath;
		CString m_strPath;
		CString m_strName;
		CString m_strExt;

	};
}