#pragma once

#include "FrameBufferDefine.h"

namespace mygl
{
	class CFrameBuffer;
	class AFX_EXT_CLASS CFrameBufferManager
	{
	public:
		CFrameBufferManager();
		virtual ~CFrameBufferManager();

	public:
		void GLCreate();
		void GLDelete();
		void GLResize(int x, int y);

		void GLBind(UINT uiType);
		void GLUnbind(UINT uiType);
		void GLBindColorTex2D(UINT uiType);
		void GLUnbindColorTex2D(UINT uiType);

	protected:
		CFrameBuffer* m_aFBO[E_FBO_NUM];

	};
}
