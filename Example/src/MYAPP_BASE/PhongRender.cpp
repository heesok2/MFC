#include "pch.h"
#include "PhongRender.h"

#include "..\MYENG_GL\PrimitiveBase.h"
#include "..\MYENG_GL\ShaderDefine.h"
#include "..\MYENG_GL\Shader.h"
#include "..\MYENG_BASE\ViewBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
	auto matViewMatrix =  pMyView->GetViewMatrix(); // glm::lookAt(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	auto matProjectionMatrix = pMyView->GetProjectionMatrix(); // glm::perspective(glm::radians(45.f), 1.f, 0.0001f, 1000.f);
	auto matNormalMatrix = glm::transpose(glm::inverse(matViewMatrix * matModelMatrix));

	pShader->GLBind();

	for (auto pPrimitive : m_aPrimitive)
	{
		if (!pPrimitive->GLIsValid())
			continue;

		pShader->GLSetMatrix4("myMatrix.matModel", matModelMatrix);
		pShader->GLSetMatrix4("myMatrix.matView", matViewMatrix);
		pShader->GLSetMatrix4("myMatrix.matProjection", matProjectionMatrix);
		pShader->GLSetMatrix4("myMatrix.matNormal", matNormalMatrix);

		pPrimitive->GLBind();
		pPrimitive->GLDraw();
		pPrimitive->GLUnbind();
	}

	pShader->GLUnbind();
}