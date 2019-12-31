#include "pch.h"
#include "AssimpFile.h"

#include "..\MYENG_LIB\StringLib.h"
#include "..\MYENG_LIB\FileCtrlLib.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\ModuleNode.h"
#include "..\MYENG_DB\ModuleElem.h"
#include "..\MYENG_DB\ModuleMesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace mylib;
using namespace mydb;

CAssimpFile::CAssimpFile(CDocBase* pDoc)
	: m_pMyDoc(pDoc)
	, m_strFilePath(_T(""))
	, m_pFile(nullptr)
{
}

CAssimpFile::~CAssimpFile()
{
}

BOOL CAssimpFile::Open(CString & strFilePath)
{
	if (!CFileCtrlLib::Exist(strFilePath))
	{
		ASSERT(g_warning);
		return FALSE;
	}
	   
	m_strFilePath = strFilePath;
	m_pFile = std::make_shared<Assimp::Importer>();

	auto FilePath = CStringLib::CSTR2STR(strFilePath, CP_UTF8);
	auto pScene = m_pFile->ReadFile(FilePath, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) // if is Not Zero
	{
		ASSERT(g_warning);
		TRACE(m_pFile->GetErrorString());
		return FALSE;
	}

	return TRUE;
}

BOOL CAssimpFile::Load()
{
	auto pScene = m_pFile->GetScene();
	if (pScene == nullptr)
	{
		ASSERT(g_warning);
		return FALSE;
	}

	auto pMyPackage = m_pMyDoc->GetPackage();
	auto pModuleNode = std::static_pointer_cast<CModuleNode>(pMyPackage->GetModule(MYTYPE_NODE));
	auto pModuleElem = std::static_pointer_cast<CModuleElem>(pMyPackage->GetModule(MYTYPE_ELEM));
	auto pModuleMesh = std::static_pointer_cast<CModuleMesh>(pMyPackage->GetModule(MYTYPE_MESH));

	CTransaction tr(pMyPackage);
	if (!tr.Begin())
		return FALSE;

	auto lambda_copy3d = [](auto& src, auto& trg)
	{
		trg.x = src.x;
		trg.y = src.y;
		trg.z = src.z;
	};
	auto lambda_copy2d = [](auto& src, auto& trg)
	{
		trg.x = src.x;
		trg.y = src.y;
	};
	for (unsigned int lmesh = 0; lmesh < pScene->mNumMeshes; ++lmesh)
	{
		std::vector<MYITR> aItrNode;
		std::vector<MYITR> aItrElem;

		auto pMesh = pScene->mMeshes[lmesh];
		for (unsigned int lnode = 0; lnode < pMesh->mNumVertices; ++lnode)
		{
			CEntityNode tNode;
			tNode.Key = pModuleNode->GetNewKey();

			lambda_copy3d(pMesh->mVertices[lnode], tNode.aVertex);
			lambda_copy3d(pMesh->mNormals[lnode], tNode.aNormal);
			lambda_copy3d(pMesh->mTangents[lnode], tNode.aTangent);
			lambda_copy3d(pMesh->mBitangents[lnode], tNode.aBitangent);

			if (pMesh->mTextureCoords[0] != nullptr)
				lambda_copy2d(pMesh->mTextureCoords[0][lnode], tNode.aTexCord);
			else
				ASSERT(g_warning);

			auto itrNode = pModuleNode->InsertNU(tNode);
			if (!ITR_IS_VALID(itrNode))
			{
				ASSERT(g_warning);
				break;
			}

			aItrNode.push_back(itrNode);
		}

		for (unsigned int lface = 0; lface < pMesh->mNumFaces; ++lface)
		{
			auto& tFace = pMesh->mFaces[lface];
			for (unsigned int indx = 0; indx < tFace.mNumIndices; indx += 3)
			{
				if (aItrNode.size() <= tFace.mIndices[indx + 0]
					|| aItrNode.size() <= tFace.mIndices[indx + 1]
					|| aItrNode.size() <= tFace.mIndices[indx + 2])
				{
					ASSERT(0);
					continue;
				}

				CEntityElem tElem;
				tElem.Key = pModuleElem->GetNewKey();
				tElem.uiType = E_ELEMTYPE_TRI3; // Only Tri3
				tElem.aItrNode.push_back(aItrNode[tFace.mIndices[indx + 0]]);
				tElem.aItrNode.push_back(aItrNode[tFace.mIndices[indx + 1]]);
				tElem.aItrNode.push_back(aItrNode[tFace.mIndices[indx + 2]]);

				auto itrElem = pModuleElem->InsertNU(tElem);
				if (ITR_IS_VALID(itrElem))
					aItrElem.push_back(itrElem);
				else
					ASSERT(g_warning);
			}
		}
		
		CEntityMesh tMesh;
		tMesh.Key = pModuleMesh->GetNewKey();
		tMesh.aItrNode = aItrNode;
		tMesh.aItrElement = aItrElem;

		auto itrMesh = pModuleMesh->InsertNU(tMesh);
		if (!ITR_IS_VALID(itrMesh))
			ASSERT(g_warning);
	}

	return tr.Commit();
}