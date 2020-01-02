#pragma once

#include "GLView.h"

#include "..\MYENG_GL\FrameBufferManager.h"
#include "..\MYENG_GL\ShaderManager.h"
#include "..\MYENG_GL\RenderManager.h"

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

	public:
		std::shared_ptr<CShader> GetShader(UINT uiShaderType);

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
		CRenderManager m_RenderManager;
		
		UINT m_uiSceneVAO;
		UINT m_uiSceneVBO;

	};
}