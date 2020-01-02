#include "pch.h"
#include "ModuleMesh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleMesh::CModuleMesh(mydb::CPackage * pPackage)
	: CModuleData<CEntityMesh>(pPackage)
{
}

CModuleMesh::~CModuleMesh()
{
}
