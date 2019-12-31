#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "MYEX.h"
#endif

#include "MYEXDoc.h"
#include "MYEXView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMYEXView, CAppViewBase)

BEGIN_MESSAGE_MAP(CMYEXView, CAppViewBase)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CAppViewBase::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CAppViewBase::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMYEXView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

CMYEXView::CMYEXView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMYEXView::~CMYEXView()
{
}

BOOL CMYEXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CAppViewBase::PreCreateWindow(cs);
}

void CMYEXView::OnDraw(CDC* pDC)
{
	CMYEXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CAppViewBase::OnDraw(pDC);
}

#ifdef _DEBUG
void CMYEXView::AssertValid() const
{
	CAppViewBase::AssertValid();
}

void CMYEXView::Dump(CDumpContext& dc) const
{
	CAppViewBase::Dump(dc);
}

CMYEXDoc* CMYEXView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMYEXDoc)));
	return (CMYEXDoc*)m_pDocument;
}
#endif //_DEBUG

void CMYEXView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMYEXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMYEXView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMYEXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMYEXView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMYEXView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}