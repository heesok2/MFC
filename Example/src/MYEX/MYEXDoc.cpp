// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를
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
#include "MyPackage.h"
#include "MyPackageStream.h"

#include "..\MYENG_LIB\ZipLib.h"
#include "..\MYENG_LIB\NotifyDefine.h"
#include "..\MYAPP_BASE\AssimpFile.h"
#include "..\MYAPP_UI\AppDialogProvider.h"


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMYEXDoc

IMPLEMENT_DYNCREATE(CMYEXDoc, CDocument)

BEGIN_MESSAGE_MAP(CMYEXDoc, CDocument)
	ON_COMMAND_RANGE(ID_MYEX_PLUGIN_UI, ID_MYEX_PLUGIN_UI, OnRibbonCategory)
	ON_COMMAND_RANGE(ID_MYEX_GTEST, ID_MYEX_GTEST, OnRibbonCategory)
	ON_COMMAND_RANGE(ID_MYEX_DIALOG, ID_MYEX_DIALOG, OnRibbonCategory)
	ON_COMMAND_RANGE(ID_MYEX_ASSIMPIMPORT, ID_MYEX_ASSIMPIMPORT, OnRibbonCategory)

	ON_UPDATE_COMMAND_UI_RANGE(ID_MYEX_PLUGIN_UI, ID_MYEX_PLUGIN_UI, OnRibbonCategoryUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MYEX_GTEST, ID_MYEX_GTEST, OnRibbonCategoryUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MYEX_DIALOG, ID_MYEX_DIALOG, OnRibbonCategoryUI)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MYEX_ASSIMPIMPORT, ID_MYEX_ASSIMPIMPORT, OnRibbonCategoryUI)
END_MESSAGE_MAP()


// CMYEXDoc 생성/소멸

CMYEXDoc::CMYEXDoc() noexcept
{
	m_pMyPackage = std::make_shared<CMyPackage>(this);
}

CMYEXDoc::~CMYEXDoc()
{
}

BOOL CMYEXDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	CMyPackageStream::New(this);

	return TRUE;
}

void CMYEXDoc::OnCloseDocument()
{
	UpdateAllViews(nullptr, E_DOCUMENT_CLOSE);

	CAppDocBase::OnCloseDocument();
}

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


std::shared_ptr<mydb::CPackage> CMYEXDoc::GetPackage()
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
			CAppDialogProvider::DoModal(this, _T("CAppListCtrlDlg"));
		}
		break;
	case ID_MYEX_PLUGIN_UI:
		{
			auto pApp = (CMYEXApp*)AfxGetApp();
			auto pExtMgr = pApp->GetExtManager();
			auto hModule = pExtMgr->GetPlugin(_T("MYEX_UI"));

			if (hModule != nullptr)
			{
				typedef BOOL(*lpFunction)(LPCTSTR, LPVOID);
				auto pFunction = (lpFunction)::GetProcAddress(hModule, "ReqService");
				if (pFunction != nullptr)
					pFunction(_T(""), nullptr);
			}
			else
			{
				AfxMessageBox(_T("Not Found MYEX_UI.dll"));
			}
		}
		break;
	case ID_MYEX_GTEST:
		{
			auto pApp = (CMYEXApp*)AfxGetApp();
			auto pExtMgr = pApp->GetExtManager();
			auto hModule = pExtMgr->GetPlugin(_T("MYPLG_GTEST"));
			if (hModule != nullptr)
			{
				typedef BOOL(*lpFunction)(LPCTSTR, LPVOID);
				auto pFunction = (lpFunction)::GetProcAddress(hModule, "ReqService");
				if (pFunction != nullptr)
					pFunction(_T(""), nullptr);
			}
			else
			{
				AfxMessageBox(_T("Not Found MYPLG_GTEST.dll"));
			}
		}
		break;
	case ID_MYEX_ASSIMPIMPORT:
		{
			CString strFilter = _T("All Files(*.*)|*.*||");
			CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, strFilter);
			if (dlg.DoModal() != IDOK)
				return;

			CAssimpFile file(this);
			auto strFilePath = dlg.GetPathName();
			if (file.Open(strFilePath))
				file.Load();
		}
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}
}

void CMYEXDoc::OnRibbonCategoryUI(CCmdUI *)
{
}