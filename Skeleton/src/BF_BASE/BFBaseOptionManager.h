#pragma once

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CBFBaseOptionManager
{
public:
	static CBFBaseOptionManager* GetInstance();

public:
	CBFBaseOptionManager(void);
	virtual ~CBFBaseOptionManager(void);

public:
	BOOL GetCheck() { return m_bCheck; }
	void SetCheck( BOOL bCheck ) { m_bCheck = bCheck; }

public:
	BOOL m_bCheck;
	long m_nFlag;
	
};
#include "HeaderPost.h"