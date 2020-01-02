#pragma once

#include "..\MYENG_BASE\ViewBase.h"

class AFX_EXT_CLASS CAppViewBase : public CViewBase
{
public:
	CAppViewBase();
	virtual ~CAppViewBase();

protected:
	virtual void OnDraw(CDC* /*pDC*/);
	
protected:
	void AttachedRender();
	void AttachedPrimitive();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP();

};