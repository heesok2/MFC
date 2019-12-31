#include "pch.h"
#include "ModuleElem.h"

CModuleElem::CModuleElem(mydb::CPackage * pPackage)
	: CModuleData<CEntityElem>(pPackage)
{
}

CModuleElem::~CModuleElem()
{
}
