#pragma once

extern "C" AFX_EXTENSION_MODULE MYPLG_UI;
class CPluginResManager
{
public:
	CPluginResManager()
	{
		m_hInst = AfxGetResourceHandle();
		AfxSetResourceHandle(MYPLG_UI.hResource);
	}

	~CPluginResManager()
	{
		AfxSetResourceHandle(m_hInst);
	}

private:
	HINSTANCE m_hInst;
};

#define SWITCH_RESOURCE  CPluginResManager _res_mgr_
