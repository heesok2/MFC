#include "stdafx.h"
#include "BFDocBase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFDocBase::CBFDocBase(void)
{
}


CBFDocBase::~CBFDocBase(void)
{
}

BOOL CBFDocBase::OnNewDocument()
{
	if( !CDocument::OnNewDocument() )
		return FALSE;

	return TRUE;
}

BOOL CBFDocBase::OnOpenDocument(LPCTSTR lpszPathName)
{
	// if( !CDocument::OnOpenDocument(lpszPathName) ) return FALSE;

	return TRUE;
}

BOOL CBFDocBase::OnSaveDocument(LPCTSTR lpszPathName)
{
	SetPathName( lpszPathName, TRUE );

	return TRUE;
}

BOOL CBFDocBase::OnSaveAsDocument(LPCTSTR lpszPathName)
{
	// Unknown 

	return TRUE;
}

void CBFDocBase::OnCloseDocument()
{
	CDocument::OnCloseDocument();
}