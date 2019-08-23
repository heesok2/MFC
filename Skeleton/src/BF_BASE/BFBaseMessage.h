#pragma once

#include "BFBaseMessageDef.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CBFBaseMessage
{
public:
	static CBFBaseMessage* GetInstance();

public:
	CBFBaseMessage(void);
	virtual ~CBFBaseMessage(void);

public:
	void SetChangedLanguage( LANG_TYPE eType );

private:
	LANG_TYPE m_eType;
};
#include "HeaderPost.h"