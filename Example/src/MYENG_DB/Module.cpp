#include "pch.h"
#include "Module.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

mydb::CModule::CModule(CPackage * pPackage)
	: m_pPackage(pPackage)
{
}

mydb::CModule::~CModule()
{
}