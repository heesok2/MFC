#pragma once

#include "GLView.h"
#include "Camera.h"

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
		glm::mat4 GetViewMatrix();
		glm::mat4 GetProjectionMatrix();

	protected:
		void GLBindFrameBuffer(UINT uiType);
		void GLUnbindFrameBuffer(UINT uiType);
		void GLCreateScene();
		void GLDeleteScene();
		
		glm::vec3 GLUnproject(CPoint point);

	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);

		DECLARE_MESSAGE_MAP();

	protected:
		CFrameBufferManager m_FrameBufferManager;
		CShaderManager m_ShaderManager;
		CRenderManager m_RenderManager;
		CCamera m_Camera;
		
		UINT m_uiSceneVAO;
		UINT m_uiSceneVBO;

	};
}