#pragma once

extern "C" AFX_EXTENSION_MODULE GTEST_DLL;
class CPluginResManager
{
public:
	CPluginResManager()
	{
		m_hInst = AfxGetResourceHandle();
		AfxSetResourceHandle(GTEST_DLL.hResource);
	}

	~CPluginResManager()
	{
		AfxSetResourceHandle(m_hInst);
	}

private:
	HINSTANCE m_hInst;
};

#define SWITCH_RESOURCE  CPluginResManager _res_mgr_
