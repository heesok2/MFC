#pragma once

namespace mydb
{
	class CPackage;
}

class AFX_EXT_CLASS CDocBase : public CDocument
{
public:
	CDocBase();
	virtual ~CDocBase();

public:
	virtual std::shared_ptr<mydb::CPackage> GetPackage() = 0;

};