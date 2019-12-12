#pragma once

class CExtDllManager
{
public:
	CExtDllManager();
	~CExtDllManager();

public:
	void LoadPlugin();
	void UnloadPlugin();

public:
	HMODULE hModule;

};

