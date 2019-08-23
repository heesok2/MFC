// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// BFPView.cpp : CBFPView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CBFPView::~CBFPView()
{
}

BEGIN_MESSAGE_MAP(CBFPView, CView)
	// ǥ�� �μ� ����Դϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CBFPView �׸���

void CBFPView::OnDraw(CDC* /*pDC*/)
{
	CBFPDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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

// CBFPView �μ�


void CBFPView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CBFPView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CBFPView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CBFPView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CBFPView ����

#ifdef _DEBUG
void CBFPView::AssertValid() const
{
	CView::AssertValid();
}

void CBFPView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBFPDoc* CBFPView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBFPDoc)));
	return (CBFPDoc*)m_pDocument;
}
#endif //_DEBUG


// CBFPView �޽��� ó����
