#include "stdafx.h"
#include "ExtDllManager.h"

CExtDllManager::CExtDllManager()
{
	hModule = nullptr;
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
		ASSERT(0);
		return;
	}

	ProgramPath = ProgramPath.Left(nFind + 1);
	ProgramPath += _T("Extension\\MYEX_DLG.dll");

	auto _hModule = ::LoadLibrary(ProgramPath);
	if (NULL == _hModule)
	{
		ASSERT(0);
		return;
	}

	hModule = _hModule;
}

void CExtDllManager::UnloadPlugin()
{
	::FreeLibrary(hModule);
}
