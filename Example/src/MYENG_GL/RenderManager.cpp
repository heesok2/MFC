#include "pch.h"
#include "RenderManager.h"
#include "RenderBase.h"
#include "PrimitiveBase.h"

using namespace mygl;

CRenderManager::CRenderManager()
{
}

CRenderManager::~CRenderManager()
{
}

void CRenderManager::AttachedRender(std::shared_ptr<CRenderBase> pRender)
{
	for (auto pAlready : m_aRender)
	{
		if (pAlready->GetType() == pRender->GetType())
		{
			ASSERT(g_warning);
			return;
		}
	}

	m_aRender.push_back(pRender);
}

void CRenderManager::AttachedPrimitive(std::shared_ptr<CPrimitiveBase> pPrimitive)
{
	for (auto pRender : m_aRender)
	{
		if (pRender->GetType() == pPrimitive->GetRenderType())
		{
			pRender->Attached(pPrimitive);
			return;
		}
	}

	ASSERT(g_warning);
}

BOOL CRenderManager::GLPrepare(CView* pView, CObject* pHint)
{
	for (auto pRender : m_aRender)
		pRender->GLPrepare(pView, pHint);

	return TRUE;
}

void mygl::CRenderManager::GLDraw(CView * pView)
{
	for (auto pRender : m_aRender)
		pRender->GLDraw(pView);
}
