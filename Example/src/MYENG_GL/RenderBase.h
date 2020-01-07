#pragma once

namespace mygl
{
	class CPrimitiveBase;
	class AFX_EXT_CLASS CRenderBase
	{
	public:
		CRenderBase();
		virtual ~CRenderBase();

	public:
		virtual UINT GetType() = 0;
		virtual void GLDraw(CView* pView) = 0;
		virtual BOOL GLPrepare(CView* pView, CObject* pHint) = 0;

	public:
		void Attached(std::shared_ptr<CPrimitiveBase> pPrimitive);		

	protected:
		std::vector<std::shared_ptr<CPrimitiveBase>> m_aPrimitive;

	};
}