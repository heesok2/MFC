#pragma once

class CGoogleTestHelper
{
	enum E_MODE { E_GTEST_CONSOLE = 0, E_GTEST_XML, E_GTEST_NUM };

public:
	CGoogleTestHelper(UINT uiMode, LPCTSTR strArgFilter);
	virtual ~CGoogleTestHelper();

public:
	BOOL Run();

protected:
	void Start();
	void PostAction();
	void Finish();

	CString GetModulePath();
	CString GetReportPath();

protected:
	UINT m_eMode;
	FILE* m_pSteam;
	CString m_strArgFilter;
	std::vector<CString> m_aArguments;
};

