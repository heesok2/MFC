#pragma once

class CExtDllManager
{
public:
	CExtDllManager();
	~CExtDllManager();

public:
	void LoadPlugin();
	void UnloadPlugin();
	HMODULE GetPlugin(CString strFileName);

public:
	std::map<CString, HMODULE> m_mExtDll;

};

