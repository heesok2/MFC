#pragma once

#include "..\BF_BASE\BFDocBase.h"

class CBFPDBSession;
class CBFPDoc : public CBFDocBase
{
	DECLARE_DYNCREATE(CBFPDoc)

public:
	CBFPDoc();
	virtual ~CBFPDoc();

public:
	virtual BOOL OnNewDocument();
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);	
	virtual BOOL OnSaveAsDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	virtual CBFDBSession* GetDBSession();
	virtual void SetDBSession( CBFDBSession* pDBSession );
	virtual int UpdateObserver( UINT Msg, WPARAM wParam, LPARAM lParam );
	
protected:
	afx_msg void OnClickedFileSave();
	afx_msg void OnRibbonCategory( UINT uiMenu );
	afx_msg void OnRibbonCategoryUI( CCmdUI* pCmdUI );
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
	
protected:
	CBFPDBSession* m_pDBSession;

};