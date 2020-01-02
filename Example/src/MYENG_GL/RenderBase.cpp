#include "pch.h"
#include "RenderBase.h"
#include "PrimitiveBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mygl;

CRenderBase::CRenderBase()
{
}

CRenderBase::~CRenderBase()
{
}

void CRenderBase::Attached(std::shared_ptr<CPrimitiveBase> pPrimitive)
{
	m_aPrimitive.push_back(pPrimitive);
}

BOOL CRenderBase::GLPrepare(CView* pView, CObject* pHint)
{
	for (auto pPrimitive : m_aPrimitive)
		pPrimitive->GLPrepare(pView, pHint);

	return TRUE;
}