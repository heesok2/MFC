#pragma once

template <int iSize>
struct TString
{
	TCHAR	str[iSize];

	TString() 
	{ 
		str[0] = NULL; 
	}
	TString(const CString& csStr)
	{
		_tcsncpy_s(str, iSize, (LPCTSTR)csStr, iSize-1);
		str[iSize-1] = NULL;
	}
	TString(LPCTSTR lpszStr)
	{
		_tcsncpy_s(str, iSize, lpszStr, iSize-1);
		str[iSize-1] = NULL;
	}
	TString& operator = (const CString csStr)
	{
		_tcsncpy_s(str, iSize, (LPCTSTR)csStr, iSize-1);
		str[iSize-1] = NULL;
		return *this;
	}
	TString& operator = (LPCTSTR lpszStr)
	{
		_tcsncpy_s(str, iSize, lpszStr, iSize-1);
		str[iSize-1] = NULL;
		return *this;
	}
	BOOL operator==(const TString& tsStr) const
	{
		if( _tcscmp( str, tsStr.str ) == 0 ) return TRUE;
		return FALSE;
	}
	BOOL operator==(const CString& cstrStr) const
	{
		if( _tcscmp( str, (LPCTSTR)cstrStr ) == 0 ) return TRUE;
		return FALSE;
	}
	BOOL operator==(LPCTSTR lpszStr) const
	{
		if( _tcscmp( str, lpszStr ) == 0 ) return TRUE;
		return FALSE;
	}
	BOOL operator!=(const TString& tsStr) const
	{
		if( _tcscmp( str, tsStr.str ) == 0 ) return FALSE;
		return TRUE;
	}
	BOOL operator!=(const CString& cstrStr) const
	{
		if( _tcscmp( str, (LPCTSTR)cstrStr ) == 0 ) return FALSE;
		return TRUE;
	}
	BOOL operator!=(LPCTSTR lpszStr) const
	{
		if( _tcscmp( str, lpszStr ) == 0 ) return FALSE;
		return TRUE;
	}
	long GetLength() const
	{
		return (long)_tcslen( str );
	}
	BOOL IsEmpty() const
	{
		return (GetLength() == 0);
	}
	operator LPCTSTR() const
	{
		return (LPCTSTR)str;
	}
};

typedef TString<32>			TShortStr;
typedef TString<64>			TStr;
typedef TString<128>		TLongStr;
typedef TString<260>		TPathStr;
typedef TString<512>        TLongPathStr;
typedef TString<1024>       TLargeStr; 