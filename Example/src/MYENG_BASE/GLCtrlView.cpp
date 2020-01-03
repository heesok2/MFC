#include "pch.h"
#include "GLCtrlView.h"

#include "..\MYENG_LIB\NotifyDefine.h"
#include "..\MYENG_GL\ShaderDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mygl;

CGLCtrlView::CGLCtrlView()
	: m_uiSceneVAO(0)
	, m_uiSceneVBO(0)
{
}

CGLCtrlView::~CGLCtrlView()
{
}

BEGIN_MESSAGE_MAP(CGLCtrlView, CGLView)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CGLCtrlView::OnDraw(CDC *)
{
	BeginwglCurrent();
	{
		GLBindFrameBuffer(E_FBO_SCREEN);

		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			auto pShader = m_ShaderManager.GetAt(E_SHADER_SCENE);

			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glDisable(GL_DEPTH_TEST);

			pShader->GLBind();
			m_FrameBufferManager.GLBindColorTex2D(E_FBO_MODEL);
			{
				glBindVertexArray(m_uiSceneVAO);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glBindVertexArray(0);
			}
			m_FrameBufferManager.GLUnbindColorTex2D(E_FBO_MODEL);
			pShader->GLUnbind();
		}
		glPopAttrib();
		SwapBuffers();

		GLUnbindFrameBuffer(E_FBO_SCREEN);
	}
	EndwglCurrent();
}

void CGLCtrlView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if (pSender == this) return;

	auto eNotify = lHint;
	switch (eNotify)
	{
	case E_DOCUMENT_DB_UPDATE:
		{
			BeginwglCurrent();
			{
				m_RenderManager.GLPrepare(this, pHint);
			}
			EndwglCurrent();
		}
		break;
	case E_DOCUMENT_CLOSE:
		{
			BeginwglCurrent();
			{
				m_FrameBufferManager.GLDelete();
				m_ShaderManager.GLDelete();

				GLDeleteScene();
			}
			EndwglCurrent();
		}
		break;
	}

	CGLView::OnUpdate(pSender, lHint, pHint);
}

void CGLCtrlView::GLCreateScene()
{
	float quadVertices[] =
	{
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenVertexArrays(1, &m_uiSceneVAO);
	glGenBuffers(1, &m_uiSceneVBO);

	glBindVertexArray(m_uiSceneVAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiSceneVBO);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
		
		auto ShaderScene = m_ShaderManager.GetAt(E_SHADER_SCENE);
		ShaderScene->GLSetInt("SceneTex2D", 0);
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CGLCtrlView::GLDeleteScene()
{
	glDeleteVertexArrays(1, &m_uiSceneVAO);
	glDeleteBuffers(1, &m_uiSceneVBO);
}

std::shared_ptr<CShader> CGLCtrlView::GetShader(UINT uiShaderType)
{
	return m_ShaderManager.GetAt(uiShaderType);
}

glm::mat4 CGLCtrlView::GetViewMatrix()
{
	return m_Camera.GetViewMatrix();
}

glm::mat4 CGLCtrlView::GetProjectionMatrix()
{
	return m_Camera.GetProjectionMatrix();
}

void CGLCtrlView::GLBindFrameBuffer(UINT uiType)
{
	m_FrameBufferManager.GLBind(uiType);
}

void CGLCtrlView::GLUnbindFrameBuffer(UINT uiType)
{
	m_FrameBufferManager.GLUnbind(uiType);
}

int CGLCtrlView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGLView::OnCreate(lpCreateStruct) == -1)
		return -1;

	BeginwglCurrent();
	{
		m_ShaderManager.GLCreate();
		m_FrameBufferManager.GLCreate();

		GLCreateScene();
	}
	EndwglCurrent();

	return 0;
}

void CGLCtrlView::OnSize(UINT nType, int cx, int cy)
{
	CGLView::OnSize(nType, cx, cy);

	CRect rect;
	rect.left = rect.bottom = 0;
	rect.right = cx;
	rect.top = cy;
	m_Camera.SetViewSize(rect);

	BeginwglCurrent();
	{
		m_FrameBufferManager.GLResize(cx, cy);
	}
	EndwglCurrent();
}