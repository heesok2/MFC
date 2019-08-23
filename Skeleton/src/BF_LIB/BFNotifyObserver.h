#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CBFNotifyObserver
{
public:
	CBFNotifyObserver(void);
	virtual ~CBFNotifyObserver(void);

public:
	virtual int UpdateObserver( UINT Msg, WPARAM wParam, LPARAM lParam );
};

#include "HeaderPost.h"