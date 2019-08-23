#pragma once

#include "..\BF_LIB\BFDBSession.h"

class DPoolTest;
class DPoolTest2;
class CBFPDBSession : public CBFDBSession
{
public:
	CBFPDBSession(void);
	virtual ~CBFPDBSession(void);

protected:
	virtual void ComposedDataPool(); 

protected:
	DPoolTest* m_pDPoolTest;
	DPoolTest2* m_pDPoolTest2;
};