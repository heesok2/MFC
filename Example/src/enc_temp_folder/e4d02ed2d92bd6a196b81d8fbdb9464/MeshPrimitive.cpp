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
	
	std::vector<glm::vec3> aBufferVertex;
	std::vector<glm::vec3> aBufferNormal;
	std::vector<glm::vec3> aBufferTexCord;

	std::vector<MYITR> aItrNode;
	auto lNodeSize = pModuleNode->GetItrList(aItrNode);
	for (auto lnode = 0; lnode < lNodeSize; ++lnode)
	{
		auto& tNode = pModuleNode->GetAtNU(aItrNode[lnode]);

		aBufferVertex.push_back(tNode.aVertex);		
		aBufferNormal.push_back(tNode.aNormal);
		aBufferTexCord.push_back(tNode.aTexCord);

		break;
	}

	std::vector<float> aBuffer;

	auto lBufferSize = (aBufferVertex.size() + aBufferNormal.size() + aBufferTexCord.size()) * 3;
	if (lBufferSize > 0)
	{
		aBuffer.resize(lBufferSize);
		auto itrNormal = std::copy(&(aBufferVertex[0][0]), &(aBufferVertex[0][0]) + (aBufferVertex.size() * 3), aBuffer.begin());
		auto itrTexCord = std::copy(&(aBufferNormal[0][0]), &(aBufferNormal[0][0]) + (aBufferNormal.size() * 3), itrNormal);
		std::copy(&(aBufferTexCord[0][0]), &(aBufferTexCord[0][0]) + (aBufferTexCord.size() * 3), itrTexCord);
	}
	
	return TRUE;
}