#pragma once

#include "..\BF_LIB\BFNotifyObserver.h"

#include "HeaderPre.h"

class CBFDBSession;
class __MY_EXT_CLASS__ CBFDocBase : public CDocument, public CBFNotifyObserver
{
public:
	CBFDocBase(void);
	virtual ~CBFDocBase(void);

protected:
	virtual BOOL OnNewDocument();	
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);	
	virtual BOOL OnSaveAsDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();

public:
	virtual CBFDBSession* GetDBSession() { ASSERT(0); return nullptr; }
	virtual void SetDBSession( CBFDBSession* pDBSession ) { ASSERT(0); }

};

#include "HeaderPost.h"