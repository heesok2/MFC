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
	: m_uiVAO(0)
	, m_uiVBO(0)
	, m_uiEBO(0)
	, m_uiSize(0)
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

	std::vector<float> aBuffer;
	std::vector<UINT> aBufferIndex;
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

	std::vector<MYITR> aItrElem;
	auto lElemSize = pModuleElem->GetItrList(aItrElem);
	for (auto lelem = 0; lelem < lElemSize; ++lelem)
	{
		auto& tElem = pModuleElem->GetAtNU(aItrElem[lelem]);
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
	   
	glGenBuffers(1, &m_uiVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * aBuffer.size(), &(aBuffer[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &m_uiEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(UINT)* aBufferIndex.size(), &(aBufferIndex[0]), GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_uiVAO);
	glBindVertexArray(m_uiVAO);
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uiEBO);

		auto itvVtx = sizeof(float) * 3 * 0;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)itvVtx);
		glEnableVertexAttribArray(0);

		auto itvNor = sizeof(float) * 3 * aBufferVertex.size();
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)itvNor);
		glEnableVertexAttribArray(1);
		
		auto itvTex = sizeof(float) * 3 * (aBufferVertex.size() + aBufferNormal.size());
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)itvTex);
		glEnableVertexAttribArray(2);
	}
	glBindVertexArray(0);

	m_uiSize = static_cast<UINT>(aBufferIndex.size());

	return TRUE;
}

BOOL CMeshPrimitive::GLIsValid()
{
	return m_uiSize;
}

void CMeshPrimitive::GLBind()
{
	glBindVertexArray(m_uiVAO);
}

void CMeshPrimitive::GLUnbind()
{
	glBindVertexArray(0);
}

void CMeshPrimitive::GLDraw()
{
	glDrawElements(GL_TRIANGLES, m_uiSize, GL_UNSIGNED_INT, 0);
}
