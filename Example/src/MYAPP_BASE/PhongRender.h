#pragma once

#include "..\MYENG_GL\RenderBase.h"

#include "RenderDefine.h"

class CPhongRender : public mygl::CRenderBase
{
public:
	CPhongRender();
	virtual ~CPhongRender();

public:
	virtual UINT GetType() override
	{
		return E_RENDER_PHONG;
	}

	virtual void GLDraw(CView* pView) override;
	virtual BOOL GLPrepare(CView* pView, CObject* pHint) override;

};