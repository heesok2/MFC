#include "pch.h"
#include "GoogleTestHelper.h"

std::string ConvertString(CString str)
{
	return std::string(CT2CA(str.operator LPCWSTR()));
};

CGoogleTestHelper::CGoogleTestHelper(UINT uiMode, LPCTSTR strArgFilter)
	: m_eMode(uiMode), m_pSteam(nullptr)
{
	//MRegistry::WriteProfileString(_T("HKEY_CURRENT_USER\\Software\\MIDAS\\TEST"), _T("LastUnitTest"), strArgFilter);

	CString strFormat = _T("");
	if (lstrcmp(strArgFilter, _T("")) != 0)
	{
		strFormat.Format(_T("%s*"), strArgFilter);
		strFormat.Replace(_T(" "), _T(","));
		strFormat.Replace(_T(",,"), _T(","));
		strFormat.Replace(_T(","), _T("*:"));
	}
	m_strArgFilter = strFormat;

	m_aArguments.clear();
	switch (uiMode)
	{
	case CGoogleTestHelper::E_GTEST_CONSOLE:
		{
			m_aArguments.push_back(GetModulePath());
		}
		break;
	case CGoogleTestHelper::E_GTEST_XML:
		{
			m_aArguments.push_back(GetModulePath());
			m_aArguments.push_back(_T("--gtest_output=xml:") + GetReportPath());
		}
		break;
	}
}

CGoogleTestHelper::~CGoogleTestHelper()
{
}

BOOL CGoogleTestHelper::Run()
{
	int argc = 0;
	TCHAR* argv[2] = {0};
	TCHAR argv_momory[2][MAX_PATH + 1];
	for (auto& str : m_aArguments)
	{
		wcscpy_s(argv_momory[argc], str.GetBuffer());
		argv[argc] = argv_momory[argc];
		if (++argc >= 2)
			break;
	}

	Start();
	{
		if (!m_strArgFilter.IsEmpty())
			::testing::GTEST_FLAG(filter) = std::string(CT2CA(m_strArgFilter.operator LPCWSTR()));
		::testing::InitGoogleTest(&argc, argv);
		::testing::FLAGS_gtest_death_test_style = "fast";

		if (RUN_ALL_TESTS() != 0)
			PostAction();
	}
	Finish();

	return TRUE;
}

void CGoogleTestHelper::Start()
{
	switch (m_eMode)
	{
	case CGoogleTestHelper::E_GTEST_CONSOLE:
		{
			if (AllocConsole())
				freopen_s(&m_pSteam, "CONOUT$", "wt", stdout);
		}
		break;
	case CGoogleTestHelper::E_GTEST_XML:
		{
		}
		break;
	}
}

void CGoogleTestHelper::PostAction()
{
	switch (m_eMode)
	{
	case CGoogleTestHelper::E_GTEST_CONSOLE:
		{
			system("pause");
		}
		break;
	case CGoogleTestHelper::E_GTEST_XML:
		{
			ShellExecute(NULL, _T("open"), GetReportPath(), _T(""), _T(""), SW_SHOW);
		}
		break;
	}
}

void CGoogleTestHelper::Finish()
{
	switch (m_eMode)
	{
	case CGoogleTestHelper::E_GTEST_CONSOLE:
		{
			if (m_pSteam)
			{
				fclose(m_pSteam);
				FreeConsole();
			}
		}
		break;
	case CGoogleTestHelper::E_GTEST_XML:
		break;
	}
}

CString CGoogleTestHelper::GetModulePath()
{
	CString strProgramPath;
	::GetModuleFileName(NULL, strProgramPath.GetBuffer(_MAX_PATH), MAX_PATH);
	strProgramPath.ReleaseBuffer();

	return strProgramPath;
}

CString CGoogleTestHelper::GetReportPath()
{
	auto strProgramPath = GetModulePath();
	if (strProgramPath.IsEmpty())
		ASSERT(0);

	auto item = strProgramPath.ReverseFind('\\');
	if (item == -1)
		ASSERT(0);

	strProgramPath = strProgramPath.Left(item) + _T("\\gTestReport.xml");

	return strProgramPath;
}
