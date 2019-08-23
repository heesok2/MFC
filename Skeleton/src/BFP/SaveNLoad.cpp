#include "stdafx.h"
#include "SaveNLoad.h"
#include "BFPDoc.h"
#include "BFPDBSession.h"

#include "..\BF_LIB\FileCtrl.h"
#include "..\BF_DATA\BFBaseFileBlockHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSaveNLoad& CSaveNLoad::Instance()
{
	static CSaveNLoad _g_singleton;
	return _g_singleton;
}

CSaveNLoad::CSaveNLoad(void)
{
}


CSaveNLoad::~CSaveNLoad(void)
{
}

BOOL CSaveNLoad::New(CBFPDoc* pDoc)
{
	auto pDBSession = new CBFPDBSession;
	if( !pDBSession )
	{
		TRACE( "CSaveNLoad : DBSession 생성 실패\n" );
		return FALSE;
	}
	else
	{
		TRACE( "CSaveNLoad : DBSession 생성 성공\n" );
		pDBSession->AttachObserver( pDoc );
	}

	pDBSession->AttachedDataPool();
	pDoc->SetDBSession( pDBSession );

	//////////////////////////////////////////////////////////////////////////

	return TRUE;
}

BOOL CSaveNLoad::Close(CBFPDoc* pDoc)
{
	auto pDBSession = pDoc->GetDBSession();
	if( !pDBSession )
	{
		TRACE( "CSaveNLoad : DBSession 소멸 실패\n" );
	}
	else
	{
		TRACE( "CSaveNLoad : DBSession 소멸 성공\n" );
		pDBSession->DettachObserver( pDoc );
	}

	_SAFE_DELETE( pDBSession );
	pDoc->SetDBSession( nullptr );

	return TRUE;
}

BOOL CSaveNLoad::Save(CBFPDoc* pDoc, LPCTSTR lpszPathName)
{
	CBFBaseFileBlockHelper helper( pDoc, CString(lpszPathName) );
	if( !helper.Write() )
	{
		TRACE( "CSaveNLoad : DB Save 실패\n" );
		return FALSE;
	}

	return TRUE;
}

BOOL CSaveNLoad::Load(CBFPDoc* pDoc, LPCTSTR lpszPathName)
{
	auto pDBSession = new CBFPDBSession;
	if( !pDBSession )
	{
		TRACE( "CSaveNLoad : DBSession 생성 실패\n" );
		return FALSE;
	}
	else
	{
		TRACE( "CSaveNLoad : DBSession 생성 성공\n" );
		pDBSession->AttachObserver( pDoc );
	}

	CFileCtrl fc(lpszPathName);
	pDoc->SetTitle( fc.GetFilePathName() );

	pDBSession->AttachedDataPool();
	pDoc->SetDBSession( pDBSession );

	//////////////////////////////////////////////////////////////////////////
	
	CBFBaseFileBlockHelper helper( pDoc, CString(lpszPathName) );
	if( !helper.Read() )
	{
		TRACE( "CSaveNLoad : DB Load 실패\n" );
		return FALSE;
	}

	return TRUE;
}