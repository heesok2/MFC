#include "pch.h"
#include "PhongRender.h"

#include "..\MYENG_GL\PrimitiveBase.h"
#include "..\MYENG_GL\ShaderDefine.h"
#include "..\MYENG_GL\Shader.h"
#include "..\MYENG_BASE\ViewBase.h"

CPhongRender::CPhongRender()
{
}

CPhongRender::~CPhongRender()
{
}

void CPhongRender::GLDraw(CView* pView)
{
	auto pMyView = reinterpret_cast<CViewBase*>(pView);
	auto pShader = pMyView->GetShader(E_SHADER_PHONG);

	pShader->GLBind();

	for (auto pPrimitive : m_aPrimitive)
	{
		if (!pPrimitive->GLIsValid())
			continue;

		pPrimitive->GLBind();
		pPrimitive->GLDraw();
		pPrimitive->GLUnbind();
	}

	pShader->GLUnbind();
}