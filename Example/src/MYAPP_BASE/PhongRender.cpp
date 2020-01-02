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
	auto matModelMatrix = glm::mat4(1.f);
	auto matViewMatrix = pMyView->GetViewMatrix();
	auto matProjectionMatrix = pMyView->GetProjectionMatrix();
	auto matNormalMatrix = glm::transpose(glm::inverse(matViewMatrix * matModelMatrix));

	pShader->GLBind();

	for (auto pPrimitive : m_aPrimitive)
	{
		if (!pPrimitive->GLIsValid())
			continue;

		pShader->GLSetMatrix4("tMatrix.matModel", matModelMatrix);
		pShader->GLSetMatrix4("tMatrix.matView", matViewMatrix);
		pShader->GLSetMatrix4("tMatrix.matProjection", matProjectionMatrix);
		pShader->GLSetMatrix4("tMatrix.matNormal", matNormalMatrix);

		pPrimitive->GLBind();
		pPrimitive->GLDraw();
		pPrimitive->GLUnbind();
	}

	pShader->GLUnbind();
}