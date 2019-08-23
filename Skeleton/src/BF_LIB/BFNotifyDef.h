#pragma once

#include <vector>

#define TR_ADD 1
#define TR_DEL 2
#define TR_MOD 3

typedef struct tagNotify
{
	UINT uiDataType;
	UINT uiMsg;
	WPARAM wParam;
	LPARAM lParam;

	tagNotify( UINT _uiDataType, UINT _uiMsg, WPARAM _wParam = NULL, LPARAM _lParam = NULL )
		: uiDataType(_uiDataType), uiMsg(_uiMsg), wParam(_wParam), lParam(_lParam)
	{
	}

} TNotify, *LPNotify;

typedef std::vector<TNotify> VEC_NOTIFY;

class CNotifyObject
{
public:
	CNotifyObject( VEC_NOTIFY* pNotify = NULL ) { m_pNotify = pNotify; }
	~CNotifyObject() { m_pNotify = NULL; }

protected:
	VEC_NOTIFY* m_pNotify;

};