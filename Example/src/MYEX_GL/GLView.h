#pragma once

namespace mygl
{
	class AFX_EXT_CLASS CGLView : public CView
	{
	public:
		CGLView();
		virtual ~CGLView();

	public:
		void BeginwglCurrent();
		void EndwglCurrent();
		void SwapBuffers();

	private:
		void CreateWGL();
		void DeleteWGL();

		void GLInitData();
		void GLInitPalette();

	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnDestroy();
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg BOOL OnQueryNewPalette();
		afx_msg void OnPaletteChanged(CWnd* pFocusWnd);

		DECLARE_MESSAGE_MAP();

	private:
		HDC m_hDC;
		HGLRC m_hRC;
		CPalette m_Palette;

	};
}

