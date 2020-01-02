#include "stdafx.h"
#include "MyPackageStream.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMyPackageStream::CMyPackageStream()
{
}

CMyPackageStream::~CMyPackageStream()
{
}

BOOL CMyPackageStream::New(CDocBase * pDoc)
{
	auto pPackage = pDoc->GetPackage();
	pPackage->CreateModule();

	return TRUE;
}

BOOL CMyPackageStream::Open(CDocBase * )
{

	return TRUE;
}

BOOL CMyPackageStream::Save(CDocBase * )
{

	return TRUE;
}

BOOL CMyPackageStream::Close(CDocBase *)
{

	return TRUE;
}
