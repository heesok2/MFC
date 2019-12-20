#pragma once

namespace mydb
{
	class CPackage;
}

#ifndef DEF_MYPACKAGE
#define DEF_MYPACKAGE

#define MYPACKAGE std::shared_ptr<mydb::CPackage>

#endif

class CExDBSession;
class AFX_EXT_CLASS CDocBase : public CDocument
{
public:
	CDocBase();
	virtual ~CDocBase();

public:
	virtual MYPACKAGE GetPackage() = 0;

};