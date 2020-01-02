#include "stdafx.h"
#include "ExtDllManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CExtDllManager::CExtDllManager()
{
}

CExtDllManager::~CExtDllManager()
{
}

void CExtDllManager::LoadPlugin()
{
	CString ProgramPath;
	::GetModuleFileName(NULL, ProgramPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	ProgramPath.ReleaseBuffer();
	int nFind = ProgramPath.ReverseFind('\\');
	if (nFind == -1)
	{
		ASSERT(g_warning);
		return;
	}

	CString ExtensionPath = ProgramPath.Left(nFind) + _T("\\Extension\\");
	if (::SetCurrentDirectory(ExtensionPath) == FALSE)
	{
		ASSERT(g_warning);
		return;
	}

	CString strFile = _T("*.dll");
	WIN32_FIND_DATA FindData;
	auto hDirectory = ::FindFirstFileEx(strFile, FindExInfoStandard, &FindData, FindExSearchNameMatch, NULL, 0);
	if (hDirectory != INVALID_HANDLE_VALUE)
	{
		do
		{
			CString strFileName = FindData.cFileName;

			if ((_tcscmp(strFileName, _T(".")) != 0) && (_tcscmp(strFileName, _T("..")) != 0))
			{
				auto hModule = ::LoadLibrary(strFileName);
				if (NULL != hModule)
				{
					auto item = strFileName.ReverseFind('.');
					if (item != -1)
						strFileName = strFileName.Left(item);

					auto itr = m_mExtDll.find(strFileName);
					if (itr != m_mExtDll.end())
					{
						ASSERT(itr->first.CompareNoCase(strFileName) == 0);
					}

					m_mExtDll[strFileName] = hModule;
				}
			}

		} while (::FindNextFile(hDirectory, &FindData));
	}
}

void CExtDllManager::UnloadPlugin()
{
	auto itr = m_mExtDll.begin();
	while (itr != m_mExtDll.end())
	{
		::FreeLibrary(itr->second);

		itr++;
	}
}

HMODULE CExtDllManager::GetPlugin(CString strFileName)
{
	auto itr = m_mExtDll.find(strFileName);
	if (itr != m_mExtDll.end())
		return itr->second;

	return NULL;
}
