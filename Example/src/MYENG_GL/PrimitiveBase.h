#pragma once

namespace mygl
{
	class AFX_EXT_CLASS CPrimitiveBase
	{
	public:
		CPrimitiveBase();
		virtual ~CPrimitiveBase();

	public:
		virtual UINT GetRenderType() = 0;
		virtual BOOL GLPrepare(CView* pView, CObject* pHint) = 0;
		virtual BOOL GLIsValid() = 0;
		virtual void GLBind() = 0;
		virtual void GLUnbind() = 0;
		virtual void GLDraw() = 0;

	};
}


