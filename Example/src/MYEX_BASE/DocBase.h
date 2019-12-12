#pragma once

class CExDBSession;
class AFX_EXT_CLASS CDocBase : public CDocument
{
public:
	CDocBase();
	virtual ~CDocBase();

public:
	virtual std::shared_ptr<CExDBSession> GetDBSession() = 0;

};