#include "stdafx.h"
#include "MYPackageStream.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"

CMYPackageStream::CMYPackageStream()
{
}

CMYPackageStream::~CMYPackageStream()
{
}

BOOL CMYPackageStream::New(CDocBase * pDoc)
{
	auto pPackage = pDoc->GetPackage();
	pPackage->CreateModule();

	return TRUE;
}

BOOL CMYPackageStream::Open(CDocBase * )
{

	return TRUE;
}

BOOL CMYPackageStream::Save(CDocBase * )
{

	return TRUE;
}

BOOL CMYPackageStream::Close(CDocBase *)
{

	return TRUE;
}
