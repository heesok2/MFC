#pragma once

#include "..\BF_LIB\BFDBSession.h"
#include "..\BF_LIB\DPool.hpp"

#include "Test2Def.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ DPoolTest2 : public DPool<CTest2>
{
public:
	DPoolTest2( CBFDBSession* pDBSession, UINT uiDataType );
	virtual ~DPoolTest2(void);

public:
	virtual BOOL ProcessRelation();
};

#include "HeaderPost.h"