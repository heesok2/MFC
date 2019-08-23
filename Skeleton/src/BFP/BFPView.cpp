// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// BFPView.cpp : CBFPView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BFP.h"
#endif

#include "BFPDoc.h"
#include "BFPView.h"

#include "..\BF_DATA\DPoolTest.h"
#include "..\BF_DATA\DPoolTest2.h"
#include "..\BF_LIB\BFNotifyDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CBFPView, CView);

CBFPView::CBFPView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CBFPView::~CBFPView()
{
}

BEGIN_MESSAGE_MAP(CBFPView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CBFPView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()

	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_BUTTON3, ID_BFPMAIN_RIBM_BUTTON3, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_BUTTON4, ID_BFPMAIN_RIBM_BUTTON4, OnRibbonCategory )

	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_BUTTON3, ID_BFPMAIN_RIBM_BUTTON3, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_BUTTON4, ID_BFPMAIN_RIBM_BUTTON4, OnRibbonCategoryUI )
END_MESSAGE_MAP()


BOOL CBFPView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CBFPView 그리기

void CBFPView::OnDraw(CDC* /*pDC*/)
{
	CBFPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


void CBFPView::OnRibbonCategory(UINT uiMenu)
{
	switch (uiMenu)
	{
	case ID_BFPMAIN_RIBM_BUTTON3:
		{
			auto pDBSession = GetDocument()->GetDBSession();
			auto pDPoolTest = (DPoolTest*)pDBSession->GetDataPool( DATATYPE_TEST );
			auto pDPoolTest2 = (DPoolTest2*)pDBSession->GetDataPool( DATATYPE_TEST2 );

			CTest tData;
			tData.Key = pDPoolTest->GetNewKey();
			tData.vPos.Set( 2 );
			tData.tData.nData = 3;
			tData.tData.dData = 4;
			tData.tData.taItr.SetSize( 5 );
			for( long indx=0; indx<5; ++indx )
				tData.tData.taItr[indx] = indx+1;

			tData.tData.tSubData.nData = 6;
			tData.tData.tSubData.dData = 7;
			tData.tData.tSubData.taItr.SetSize(8);
			for( long indx=0; indx<8; ++indx )
				tData.tData.tSubData.taItr[indx] = indx+1;

			tData.taData.SetSize( 9 );
			for( long indx=0; indx<9; ++indx )
			{
				tData.taData[indx].nData = indx+1;
				tData.taData[indx].dData = (double)(indx+1);
				tData.taData[indx].taItr.SetSize( indx+1 );
				for( long indx2=0; indx2<(indx+1); ++indx2 )
					tData.taData[indx].taItr[indx2] = indx2+1;

				tData.taData[indx].tSubData.nData = indx+1;
				tData.taData[indx].tSubData.dData = (double)(indx+1);
				tData.taData[indx].tSubData.taItr.SetSize(indx+1);
				for( long indx2=0; indx2<(indx+1); ++indx2 )
					tData.taData[indx].tSubData.taItr[indx2] = indx2+1;
			}

			CTransaction tr( GetDocument()->GetDBSession() );
			if( !tr.Begin(_T("TEST")) ) break;

			TIterator itrTest = pDPoolTest->InsertNU( tData );
			if( ITR_IS_VALID(itrTest) )
			{
				auto tData = pDPoolTest->GetAtNU( itrTest );
				if( tData.Key != tData.Key )
				{
					ASSERT(0);
				}
			}

			CTest2 tTest2;
			tTest2.Key = pDPoolTest2->GetNewKey();
			tTest2.taItrTest.SetSize( 1 );
			tTest2.taItrTest[0] = itrTest;

			TIterator itrTest2 = pDPoolTest2->InsertNU( tTest2 );

			if( !tr.Commit() ) break;
		}
		break;
	case ID_BFPMAIN_RIBM_BUTTON4:
		{
			auto pDBSession = GetDocument()->GetDBSession();
			auto pDPoolTest = (DPoolTest*)pDBSession->GetDataPool( DATATYPE_TEST );

			TArrayITR taItr;
			auto lDataSize = pDPoolTest->GetItrList( taItr );
			for( long indx=0; indx<lDataSize; ++indx )
			{
				auto tData = pDPoolTest->GetAtNU( taItr[indx] );

				if( tData.Key )
				{
					int i = 0;
				}
			}


// 			class CD1
// 			{
// 			public:
// 				CD1() {}
// 				~CD1() {}
// 
// 			public: 
// 				int i;
// 			};
// 
// 			class CD2
// 			{
// 			public:
// 				CD2() {}
// 				~CD2() { taCD1.RemoveAll(); }
// 
// 			public:
// 				TArray<CD1> taCD1;
// 			};
// 
// 			class CD3
// 			{
// 			public:
// 				CD3() {}
// 				~CD3() 
// 				{ 
// 					long lSize = taCD2.GetSize();
// 					for( long indx=0; indx<lSize; ++indx )
// 						taCD2[indx].taCD1.RemoveAll();
// 
// 					taCD2.RemoveAll(); 
// 				}
// 
// 			public:
// 				TArray<CD2> taCD2;
// 			};
// 
// 
// 			CD3 tData;
// 			tData.taCD2.SetSize( 3 );
// 			for( long indx=0; indx<3; ++indx )
// 			{
// 				tData.taCD2[indx].taCD1.SetSize(4);
// 			}
		}
		break;
	default:
		break;
	}
}

void CBFPView::OnRibbonCategoryUI(CCmdUI* pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_BFPMAIN_RIBM_BUTTON3:
	case ID_BFPMAIN_RIBM_BUTTON4:
		{
			pCmdUI->Enable( TRUE );
		}
		break;
	default:
		break;
	}
}

// CBFPView 인쇄


void CBFPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBFPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CBFPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CBFPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CBFPView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBFPView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBFPView 진단

#ifdef _DEBUG
void CBFPView::AssertValid() const
{
	CView::AssertValid();
}

void CBFPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBFPDoc* CBFPView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBFPDoc)));
	return (CBFPDoc*)m_pDocument;
}
#endif //_DEBUG


// CBFPView 메시지 처리기
