#include "pch.h"
#include "MYAPPView.h"

CMYAPPView::CMYAPPView()
{
}

CMYAPPView::~CMYAPPView()
{
}

void CMYAPPView::OnDraw(CDC * pDC)
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


		}

		glPopAttrib();
		glPopMatrix();

		GLUnbindFrameBuffer(E_FBO_MODEL);
	}
	EndwglCurrent();
	
	CViewBase::OnDraw(pDC);
}