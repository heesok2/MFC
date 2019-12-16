#pragma once

class CPackage;
class AFX_EXT_CLASS CModule
{
public:
	CModule(CPackage* pPackage);
	virtual ~CModule();
		
protected:
	CPackage* m_pPackage;

};