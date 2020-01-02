#include "pch.h"
#include "AppViewBase.h"
#include "PhongRender.h"
#include "MeshPrimitive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAppViewBase::CAppViewBase()
{

}

CAppViewBase::~CAppViewBase()
{
}

BEGIN_MESSAGE_MAP(CAppViewBase, CViewBase)

	ON_WM_CREATE()
END_MESSAGE_MAP()

void CAppViewBase::OnDraw(CDC * pDC)
{
	BeginwglCurrent();
	{
		GLBindFrameBuffer(E_FBO_MODEL);

		glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		{
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);

			//m_RenderManager.GLDraw(this);
		}

		glPopAttrib();
		glPopMatrix();

		GLUnbindFrameBuffer(E_FBO_MODEL);
	}
	EndwglCurrent();

	CViewBase::OnDraw(pDC);
}

void CAppViewBase::AttachedRender()
{
	//m_RenderManager.AttachedRender(std::make_shared<CPhongRender>());
}

void CAppViewBase::AttachedPrimitive()
{
	//m_RenderManager.AttachedPrimitive(std::make_shared<CMeshPrimitive>());
}

int CAppViewBase::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CViewBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	AttachedRender();

	AttachedPrimitive();

	return 0;
}
