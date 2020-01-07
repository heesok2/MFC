#include "pch.h"
#include "MeshPrimitive.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_BASE\ViewBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\ModuleNode.h"
#include "..\MYENG_DB\ModuleElem.h"
#include "..\MYENG_DB\ModuleMesh.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMeshPrimitive::CMeshPrimitive()
{
}

CMeshPrimitive::~CMeshPrimitive()
{
}

BOOL CMeshPrimitive::GLPrepare(CView * pView)
{
	auto pMyDoc = static_cast<CDocBase*>(pView->GetDocument());
	auto pPackage = pMyDoc->GetPackage();
	auto pModuleNode = std::static_pointer_cast<CModuleNode>(pPackage->GetModule(MYTYPE_NODE));
	auto pModuleElem = std::static_pointer_cast<CModuleElem>(pPackage->GetModule(MYTYPE_ELEM));
	auto pModuleMesh = std::static_pointer_cast<CModuleMesh>(pPackage->GetModule(MYTYPE_MESH));

	if (pModuleNode->Empty() ||
		pModuleElem->Empty() ||
		pModuleMesh->Empty())
		return TRUE;

	std::vector<float> aBuffer;
	std::vector<glm::vec3> aBufferVertex;
	std::vector<glm::vec3> aBufferNormal;
	std::vector<glm::vec2> aBufferTexCord;

	std::vector<MYITR> aItrNode;
	std::map<MYITR, UINT> mNodeIndex;
	auto lNodeSize = pModuleNode->GetItrList(aItrNode);
	for (auto lnode = 0; lnode < lNodeSize; ++lnode)
	{
		auto& tNode = pModuleNode->GetAtNU(aItrNode[lnode]);
		aBufferVertex.push_back(tNode.aVertex);
		aBufferNormal.push_back(tNode.aNormal);
		aBufferTexCord.push_back(tNode.aTexCord);

		mNodeIndex[aItrNode[lnode]] = lnode;
	}

	auto lBufferSize = (aBufferVertex.size() + aBufferNormal.size()) * 3 + aBufferTexCord.size() * 2;
	if (lBufferSize > 0)
	{
		aBuffer.resize(lBufferSize);
		auto itrNormal = std::copy(&(aBufferVertex[0][0]), &(aBufferVertex[0][0]) + (aBufferVertex.size() * 3), aBuffer.begin());
		auto itrTexCord = std::copy(&(aBufferNormal[0][0]), &(aBufferNormal[0][0]) + (aBufferNormal.size() * 3), itrNormal);
		std::copy(&(aBufferTexCord[0][0]), &(aBufferTexCord[0][0]) + (aBufferTexCord.size() * 2), itrTexCord);
	}

	auto uiVBO = CreateVBO(aBuffer);

	/////////////////////////////////////////////////////////////////////////

	std::vector<MYITR> aItrMesh;
	auto lMeshSize = pModuleMesh->GetItrList(aItrMesh);
	for (auto lmesh = 0; lmesh < lMeshSize; ++lmesh)
	{
		std::vector<UINT> aBufferIndex;

		auto& tMesh = pModuleMesh->GetAtNU(aItrMesh[lmesh]);
		for (auto itrElem : tMesh.aItrElem)
		{
			auto& tElem = pModuleElem->GetAtNU(itrElem);
			if (tElem.uiType == E_ELEMTYPE_TRI3)
			{
				aBufferIndex.push_back(mNodeIndex[tElem.aItrNode[0]]);
				aBufferIndex.push_back(mNodeIndex[tElem.aItrNode[1]]);
				aBufferIndex.push_back(mNodeIndex[tElem.aItrNode[2]]);
			}
			else
			{
				ASSERT(g_warning);
			}
		}

		auto uiEBO = CreateEBO(aBufferIndex);

		UINT uiNormalOffset = 3 * sizeof(float) * static_cast<UINT>(aBufferVertex.size());
		UINT uiTexcelOffset = 3 * sizeof(float) * static_cast<UINT>(aBufferVertex.size() + aBufferNormal.size());
		CreateVAO(uiVBO, uiEBO, static_cast<UINT>(aBufferIndex.size())
				  , 3, 0
				  , 3, uiNormalOffset
				  , 2, uiTexcelOffset);

		//auto uiTex = CreateTex2D(GL_RGB, )
	}

	return TRUE;
}