#pragma once

#include "..\MYENG_BASE\ViewBase.h"

class AFX_EXT_CLASS CMYAPPView : public CViewBase
{
public:
	CMYAPPView();
	virtual ~CMYAPPView();

protected:

	virtual void OnDraw(CDC* /*pDC*/);
};

