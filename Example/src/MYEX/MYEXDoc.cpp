﻿// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해
// 추가적으로 제공되는 내용입니다.
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// MYEXDoc.cpp: CMYEXDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MYEX.h"
#endif

#include "MYEXDoc.h"
#include "MYPackage.h"
#include "..\MYEX_LIB\ExMathLib.h"
#include "..\MYEX_LIB\ZipLib.h"
#include "..\MYEX_DB\ExDBSession.h"
#include "..\MYAPP_UI\AppDialogProvider.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMYEXDoc

IMPLEMENT_DYNCREATE(CMYEXDoc, CDocument)

BEGIN_MESSAGE_MAP(CMYEXDoc, CDocument)
	ON_COMMAND_RANGE(ID_PANEL_BUTTON_L, ID_PANEL_BUTTON_L, OnRibbonCategory)
	ON_COMMAND_RANGE(ID_PANEL_BUTTON_S, ID_PANEL_BUTTON_S, OnRibbonCategory)
	ON_COMMAND_RANGE(ID_MYEX_DIALOG, ID_MYEX_DIALOG, OnRibbonCategory)

	ON_UPDATE_COMMAND_UI_RANGE(ID_PANEL_BUTTON_L, ID_PANEL_BUTTON_L, OnRibbonCategoryUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_PANEL_BUTTON_S, ID_PANEL_BUTTON_S, OnRibbonCategoryUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MYEX_DIALOG, ID_MYEX_DIALOG, OnRibbonCategoryUI)
END_MESSAGE_MAP()


// CMYEXDoc 생성/소멸

CMYEXDoc::CMYEXDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_pDBSession = std::make_shared<CExDBSession>();
	m_pMyPackage = new CMYPackage();
}

CMYEXDoc::~CMYEXDoc()
{
	_SAFE_DEL(m_pMyPackage);
}

BOOL CMYEXDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMYEXDoc serialization

void CMYEXDoc::Serialize(CArchive& ar)
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
void CMYEXDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMYEXDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMYEXDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMYEXDoc 진단

#ifdef _DEBUG
void CMYEXDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMYEXDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

// CMYEXDoc 명령


CPackage * CMYEXDoc::GetPackage()
{
	ASSERT(m_pMyPackage != nullptr);
	return m_pMyPackage;
}

void CMYEXDoc::OnRibbonCategory(UINT uiMenu)
{
	switch (uiMenu)
	{
	case ID_MYEX_DIALOG:
		{
			CAppDialogProvider::DoModal(this, _T("CExampleDlg"));
		}
		break;
	case ID_PANEL_BUTTON_L:
		{
			auto pApp = (CMYEXApp*)AfxGetApp();

			typedef BOOL(*lpFunction)(LPCTSTR, LPVOID);
			auto pFunction = (lpFunction)::GetProcAddress(pApp->m_ExtDllManager.hModule, "ReqService");
			if (pFunction != nullptr)
				pFunction(_T(""), nullptr);
		}
		break;
	case ID_PANEL_BUTTON_S:
		{
			CString ProgramPath;
			::GetModuleFileName(NULL, ProgramPath.GetBuffer(_MAX_PATH), _MAX_PATH);
			ProgramPath.ReleaseBuffer();

			int nFind = ProgramPath.ReverseFind('\\');
			if (nFind == -1)
			{
				ASSERT(g_warning);
				return;
			}

			ProgramPath = ProgramPath.Left(nFind + 1);
			ProgramPath += _T("Extension\\MYEX_GTEST.dll");

			auto hModule = ::LoadLibrary(ProgramPath);
			if (NULL == hModule)
			{
				ASSERT(g_warning);
				return;
			}

			typedef BOOL(*lpFunction)(LPCTSTR, LPVOID);
			auto pFunction = (lpFunction)::GetProcAddress(hModule, "ReqService");
			if (pFunction != nullptr)
				pFunction(_T(""), nullptr);

			::FreeLibrary(hModule);
		}
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}
}

void CMYEXDoc::OnRibbonCategoryUI(CCmdUI * pCmdUI)
{
	switch (pCmdUI->m_nID)
	{
	case ID_PANEL_BUTTON_L:
	case ID_PANEL_BUTTON_S:
		{

		}
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}
}