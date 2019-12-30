#include "pch.h"
#include "StringLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

mylib::CStringLib::CStringLib()
{
}


mylib::CStringLib::~CStringLib()
{
}

void mylib::CStringLib::CSTR2WSTR(IN const CString & cstr, OUT std::wstring wstr)
{
	wstr = CSTR2WSTR(cstr);
}

void mylib::CStringLib::WSTR2CSTR(IN const std::wstring & wstr, OUT CString & cstr)
{
	cstr = WSTR2CSTR(wstr);
}

void mylib::CStringLib::CSTR2STR(IN const CString & cstr, OUT std::string & str, UINT CodePage)
{
	str = CSTR2STR(cstr, CodePage);
}

void mylib::CStringLib::STR2CSTR(IN const std::string & str, OUT CString & cstr, UINT CodePage)
{
	cstr = STR2CSTR(str, CodePage);
}

void mylib::CStringLib::STR2WSTR(IN const std::string & str, OUT std::wstring wstr, UINT CodePage)
{
	wstr = STR2WSTR(str, CodePage);
}

void mylib::CStringLib::WSTR2STR(IN const std::wstring wstr, OUT std::string & str, UINT CodePage)
{
	str = WSTR2STR(wstr, CodePage);
}

std::wstring mylib::CStringLib::CSTR2WSTR(IN const CString & cstr)
{
	return std::wstring(cstr.operator LPCWSTR());
}

CString mylib::CStringLib::WSTR2CSTR(IN const std::wstring & wstr)
{
	return CString::CStringT(wstr.c_str());
}

std::string mylib::CStringLib::CSTR2STR(IN const CString & cstr, UINT CodePage)
{
	return std::string(CT2CA(cstr.operator LPCWSTR(), CodePage));
}

CString mylib::CStringLib::STR2CSTR(IN const std::string & str, UINT CodePage)
{
	return CString::CStringT(CA2CT(str.c_str(), CodePage));
}

std::wstring mylib::CStringLib::STR2WSTR(IN const std::string & str, UINT CodePage)
{
	return std::wstring(CA2CT(str.c_str(), CodePage));
}

std::string mylib::CStringLib::WSTR2STR(IN const std::wstring wstr, UINT CodePage)
{
	return std::string(CT2CA(wstr.c_str(), CodePage));
}

