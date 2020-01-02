#pragma once

namespace mygl
{
	class CRenderBase;
	class CPrimitiveBase;
	class AFX_EXT_CLASS CRenderManager
	{
	public:
		CRenderManager();
		virtual ~CRenderManager();

	public:
		void AttachedRender(std::shared_ptr<CRenderBase> pRender);
		void AttachedPrimitive(std::shared_ptr<CPrimitiveBase> pPrimitive);

		BOOL GLPrepare(CView* pView, CObject* pHint);

	protected:
		std::vector<std::shared_ptr<CRenderBase>> m_aRender;

	};
}