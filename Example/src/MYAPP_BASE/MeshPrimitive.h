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

	virtual BOOL GLPrepare(CView* pView, CObject* pHint) override;
	virtual BOOL GLIsValid() override;
	virtual void GLBind() override;
	virtual void GLUnbind() override;
	virtual void GLDraw() override;

protected:
	UINT m_uiVAO;
	UINT m_uiVBO;
	UINT m_uiEBO;
	UINT m_uiSize;

};

