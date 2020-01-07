#pragma once

#include "..\MYENG_GL\PrimitiveBase.h"

#include "RenderDefine.h"

class CMeshPrimitive : public mygl::CPrimitiveBase
{
public:
	CMeshPrimitive();
	virtual ~CMeshPrimitive();

public:
	virtual UINT GetRenderType() override
	{
		return E_RENDER_PHONG;
	}

	virtual BOOL GLPrepare(CView* pView) override;
};