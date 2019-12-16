#pragma once

class CPackage;
class CExDBSession;
class AFX_EXT_CLASS CDocBase : public CDocument
{
public:
	CDocBase();
	virtual ~CDocBase();

public:
	virtual CPackage* GetPackage() = 0;
	virtual std::shared_ptr<CExDBSession> GetDBSession() = 0;

};