#pragma once

#include "GLView.h"

#include "..\MYEX_GL\FrameBufferManager.h"
#include "..\MYEX_GL\ShaderManager.h"

namespace mygl
{
	class AFX_EXT_CLASS CGLCtrlView : public CGLView
	{
	public:
		CGLCtrlView();
		virtual ~CGLCtrlView();

	protected:
		virtual void OnDraw(CDC* /*pDC*/);
		virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

	protected:
		void GLBindFrameBuffer(UINT uiType);
		void GLUnbindFrameBuffer(UINT uiType);
		void GLCreateScene();
		void GLDeleteScene();

	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);

		DECLARE_MESSAGE_MAP();

	protected:
		CFrameBufferManager m_FrameBufferManager;
		CShaderManager m_ShaderManager;
		UINT m_uiSceneVAO;
		UINT m_uiSceneVBO;

	};
}