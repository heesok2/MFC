#pragma once

#include "..\MYAPP_BASE\AppViewBase.h"

class CMYEXView : public CAppViewBase
{
protected: // serialization에서만 만들어집니다.
	CMYEXView() noexcept;
	DECLARE_DYNCREATE(CMYEXView)

public:
	virtual ~CMYEXView();

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	CMYEXDoc* GetDocument() const;

protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()

};

#ifndef _DEBUG  // MYEXView.cpp의 디버그 버전
inline CMYEXDoc* CMYEXView::GetDocument() const
{
	return reinterpret_cast<CMYEXDoc*>(m_pDocument);
}
#endif