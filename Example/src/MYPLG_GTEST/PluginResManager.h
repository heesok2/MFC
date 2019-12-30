#pragma once

extern "C" AFX_EXTENSION_MODULE MYPLG_GTEST;
class CPluginResManager
{
public:
	CPluginResManager()
	{
		m_hInst = AfxGetResourceHandle();
		AfxSetResourceHandle(MYPLG_GTEST.hResource);
	}

	~CPluginResManager()
	{
		AfxSetResourceHandle(m_hInst);
	}

private:
	HINSTANCE m_hInst;
};

#define SWITCH_RESOURCE  CPluginResManager _res_mgr_
