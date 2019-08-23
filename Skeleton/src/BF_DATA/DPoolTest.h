#pragma once

#include "..\BF_LIB\BFDBSession.h"
#include "..\BF_LIB\DPool.hpp"

#include "TestDef.h"
#include "HeaderPre.h"

class __MY_EXT_CLASS__ DPoolTest : public DPool<CTest>
{
public:
	DPoolTest( CBFDBSession* pDBSession, UINT uiDataType );
	virtual ~DPoolTest(void);
};

#include "HeaderPost.h"