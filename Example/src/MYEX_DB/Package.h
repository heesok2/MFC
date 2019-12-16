#pragma once

class CModule;
class AFX_EXT_CLASS CPackage
{
public:
	CPackage();
	virtual ~CPackage();
	
public:
	virtual void CreateModule() = 0;

protected:
	std::map<ETYPE, CModule*> m_mModule;

};