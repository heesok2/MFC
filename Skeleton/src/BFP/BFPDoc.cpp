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

// BFPDoc.cpp : CBFPDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "BFP.h"
#endif

#include "BFPDoc.h"
#include "BFPDBSession.h"
#include "SaveNLoad.h"

#include <propkey.h>
#include "..\BF_LIB\IBFProduct.h"
#include "..\BF_LIB\FileDialogEx.h"
#include "..\BF_LIB\BFNotifyDef.h"
#include "..\BF_BASE\BFBaseDlg.h"
#include "..\BF_BASE\BFBaseMessage.h"
#include "..\BF_BASE\BFBaseOptionManager.h"
#include "..\BF_DATA\DPoolTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CBFPDoc, CBFDocBase);

CBFPDoc::CBFPDoc() : m_pDBSession( nullptr )
{
}

CBFPDoc::~CBFPDoc()
{
	ASSERT( m_pDBSession == nullptr );
}

BEGIN_MESSAGE_MAP(CBFPDoc, CBFDocBase)
	ON_BN_CLICKED( ID_FILE_SAVE, OnClickedFileSave )

	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_BUTTON1, ID_BFPMAIN_RIBM_BUTTON1, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_CHECKBOX1, ID_BFPMAIN_RIBM_CHECKBOX1, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_BUTTONMENU, ID_BFPMAIN_RIBM_BUTTONMENU, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_BUTTONMENU1, ID_BFPMAIN_RIBM_BUTTONMENU1, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_BUTTONMENU2, ID_BFPMAIN_RIBM_BUTTONMENU2, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_COMBOBOX1, ID_BFPMAIN_RIBM_COMBOBOX1, OnRibbonCategory )
	ON_COMMAND_RANGE( ID_BFPMAIN_RIBM_COMBOBOX2, ID_BFPMAIN_RIBM_COMBOBOX2, OnRibbonCategory )

	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_BUTTON1, ID_BFPMAIN_RIBM_BUTTON1, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_CHECKBOX1, ID_BFPMAIN_RIBM_CHECKBOX1, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_BUTTONMENU, ID_BFPMAIN_RIBM_BUTTONMENU, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_BUTTONMENU1, ID_BFPMAIN_RIBM_BUTTONMENU1, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_BUTTONMENU2, ID_BFPMAIN_RIBM_BUTTONMENU2, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_COMBOBOX1, ID_BFPMAIN_RIBM_COMBOBOX1, OnRibbonCategoryUI )
	ON_UPDATE_COMMAND_UI_RANGE( ID_BFPMAIN_RIBM_COMBOBOX2, ID_BFPMAIN_RIBM_COMBOBOX2, OnRibbonCategoryUI )
END_MESSAGE_MAP()


BOOL CBFPDoc::OnNewDocument()
{
	if( !CBFDocBase::OnNewDocument() )
		return FALSE;

	if( !CSaveNLoad::Instance().New( this ) )
		return FALSE;

	return TRUE;
}

BOOL CBFPDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if( !CBFDocBase::OnOpenDocument(lpszPathName) )
		return FALSE;

	if( !CSaveNLoad::Instance().Load(this, lpszPathName) ) 
		return FALSE;

	return TRUE;
}

BOOL CBFPDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if( !CSaveNLoad::Instance().Save(this, lpszPathName) ) 
		return FALSE;

	return CBFDocBase::OnSaveDocument(lpszPathName);
}

BOOL CBFPDoc::OnSaveAsDocument(LPCTSTR lpszPathName)
{
	return OnSaveDocument(lpszPathName);
}

void CBFPDoc::OnCloseDocument()
{
	if( !CSaveNLoad::Instance().Close( this ) )
		return;

	CBFDocBase::OnCloseDocument();
}

// CBFPDoc serialization

void CBFPDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CBFPDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CBFPDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBFPDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBFPDoc 진단

#ifdef _DEBUG

void CBFPDoc::AssertValid() const
{
	CBFDocBase::AssertValid();
}

void CBFPDoc::Dump(CDumpContext& dc) const
{
	CBFDocBase::Dump(dc);
}

#endif //_DEBUG

CBFDBSession* CBFPDoc::GetDBSession()
{
	return m_pDBSession;
}

void CBFPDoc::SetDBSession(CBFDBSession* pDBSession)
{
	m_pDBSession = static_cast<CBFPDBSession*>(pDBSession);
}

int CBFPDoc::UpdateObserver(UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch( Msg )
	{
	case DB_NOTIFY_UPDATE:
		{
			auto pDPoolTest = (DPoolTest*)m_pDBSession->GetDataPool( DATATYPE_TEST );
			
			TArrayITR taItr;
			long lSize = pDPoolTest->GetItrList( taItr );
			for( long indx=0; indx<lSize; ++indx )
			{
				auto tData = pDPoolTest->GetAtNU( taItr[indx] );
				if( tData.Key > 0 )
				{
					int i = 0;
				}
			}
		}
		break;
	default:
		break;
	}

	return 0;
}

void CBFPDoc::OnClickedFileSave()
{
	CString strFileName = GetPathName();
	if( strFileName.IsEmpty() )
	{
		CFileDialogEx fileDialog( this, FALSE, IBFProduct::GetInstance()->GetProductExt(), GetTitle(), OFN_OVERWRITEPROMPT, IBFProduct::GetInstance()->GetProductFilter(), NULL );
		if( fileDialog.DoModal() != IDOK ) return;

		SetTitle( fileDialog.GetFileTitle() );
		strFileName = fileDialog.GetPathName();
	}

	OnSaveDocument(strFileName);
}

void CBFPDoc::OnRibbonCategory(UINT uiMenu)
{
	auto pInstance = CBFBaseOptionManager::GetInstance();
	switch (uiMenu)
	{
	case ID_BFPMAIN_RIBM_BUTTON1:
	case ID_BFPMAIN_RIBM_BUTTON2:
		{
			CBFBaseMessage msg;
			msg.SetChangedLanguage( LANG_KR );

			// 			CBFPBaseDlg dlg;
			// 			dlg.DoModal();
		}
		break;

	case ID_BFPMAIN_RIBM_BUTTONMENU:
		{

		}
		break;
	case ID_BFPMAIN_RIBM_BUTTONMENU1:
		{
			pInstance->m_nFlag = 0;
		}
		break;
	case ID_BFPMAIN_RIBM_BUTTONMENU2:
		{
			pInstance->m_nFlag = 1;
		}
		break;
	case ID_BFPMAIN_RIBM_CHECKBOX1:
		{
			pInstance->SetCheck( !pInstance->GetCheck() );
		}
		break;

	case ID_BFPMAIN_RIBM_COMBOBOX1:
	case ID_BFPMAIN_RIBM_COMBOBOX2:
		{

		}
		break;
	default:
		break;
	}
}

void CBFPDoc::OnRibbonCategoryUI(CCmdUI* pCmdUI)
{
	auto pInstance = CBFBaseOptionManager::GetInstance();
	switch (pCmdUI->m_nID)
	{
	case ID_BFPMAIN_RIBM_BUTTON1:
	case ID_BFPMAIN_RIBM_BUTTON2:
	case ID_BFPMAIN_RIBM_BUTTONMENU:
		{

		}
		break;
	case ID_BFPMAIN_RIBM_BUTTONMENU1:
		{
			pCmdUI->SetCheck( pInstance->m_nFlag == 0 );
			pCmdUI->Enable( FALSE );
		}
		break;
	case ID_BFPMAIN_RIBM_BUTTONMENU2:
		{
			pCmdUI->SetCheck( pInstance->m_nFlag == 1 );
			pCmdUI->Enable( TRUE );
		}
		break;
	case ID_BFPMAIN_RIBM_CHECKBOX1:
		{
			pCmdUI->SetCheck( pInstance->m_bCheck );
		}
		break;
	case ID_BFPMAIN_RIBM_COMBOBOX1:
	case ID_BFPMAIN_RIBM_COMBOBOX2:
		{

		}
		break;
	default:
		break;
	}
}