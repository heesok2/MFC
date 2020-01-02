#include "pch.h"
#include "ModuleElem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleElem::CModuleElem(mydb::CPackage * pPackage)
	: CModuleData<CEntityElem>(pPackage)
{
}

CModuleElem::~CModuleElem()
{
}
