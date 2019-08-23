#pragma once

#include <vector>
#include "HeaderPre.h"

#define DB_NOTIFY_UNKNOWN	0x0000
#define DB_NOTIFY_UPDATE	0x0001

class CBFNotifyObserver;
class __MY_EXT_CLASS__ CBFNotifyManager
{
	typedef std::vector<CBFNotifyObserver*> VEC_OBSERVER;

public:
	CBFNotifyManager(void);
	virtual ~CBFNotifyManager(void);

public:
	virtual void ClearObservers();
	virtual void AttachObserver( CBFNotifyObserver* pObsv );
	virtual void DettachObserver( CBFNotifyObserver* pObsv );

	virtual int Notify( UINT Msg, WPARAM wParam = NULL, LPARAM lParam = NULL );
	
protected:
	VEC_OBSERVER m_vObserver;

};

#include "HeaderPost.h"