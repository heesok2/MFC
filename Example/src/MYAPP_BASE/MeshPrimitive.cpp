#include "pch.h"
#include "MeshPrimitive.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_BASE\ViewBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\ModuleNode.h"
#include "..\MYENG_DB\ModuleElem.h"
#include "..\MYENG_DB\ModuleMesh.h"

CMeshPrimitive::CMeshPrimitive()
{
}

CMeshPrimitive::~CMeshPrimitive()
{
}

BOOL CMeshPrimitive::GLPrepare(CView * pView, CObject *)
{
	auto pMyDoc = static_cast<CDocBase*>(pView->GetDocument());
	auto pPackage = pMyDoc->GetPackage();
	auto pModuleNode = std::static_pointer_cast<CModuleNode>(pPackage->GetModule(MYTYPE_NODE));
	auto pModuleElem = std::static_pointer_cast<CModuleElem>(pPackage->GetModule(MYTYPE_ELEM));
	auto pModuleMesh = std::static_pointer_cast<CModuleMesh>(pPackage->GetModule(MYTYPE_MESH));
	
	std::vector<MYITR> aItrMesh;
	auto lMeshSize = pModuleMesh->GetItrList(aItrMesh);

	for (auto itrMesh : aItrMesh)
	{
		auto tMesh = pModuleMesh->GetAtNU(itrMesh);

	}

	return TRUE;
}