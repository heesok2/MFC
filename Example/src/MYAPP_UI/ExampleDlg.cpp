#include "pch.h"
#include "Resource.h"
#include "ExampleDlg.h"
#include "ModernExample.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\ModuleNode.h"
#include "..\MYENG_DB\ModuleElem.h"
#include "..\MYENG_DB\ModuleMesh.h"

#include "..\MYAPP_BASE\MyTarget.h"

using namespace mydb;

enum E_EXAMPLE_COBX
{
	E_COBX_UNKNOWN = -1
	, E_COBX_TEST = 0
	, E_COBX_MESH_FACE
	, E_COBX_MESH_BOX
	, E_COBX_MODERN

	, E_COBX_NUM
};

CString g_example_name[E_COBX_NUM] =
{
	_T("Test")			// E_COBX_TEST
	, _T("Mesh - Face")	// E_COBX_MESH_FACE
	, _T("Mesh - Box")	// E_COBX_MESH_BOX
	, _T("Modern C++")	// E_COBX_MODERN
};

CExampleDlg::CExampleDlg(CDocBase * pDoc, CWnd * pParent)
	: CMyDialog(CExampleDlg::IDD, pDoc, pParent)
{
}

CExampleDlg::~CExampleDlg()
{
}

void CExampleDlg::DoDataExchange(CDataExchange * pDX)
{
	CMyDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYAPPUI_COBX, m_cobx);
}

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)
	ON_BN_CLICKED(IDC_MYAPPUI_APPLY, OnClickedApply)
END_MESSAGE_MAP();

BOOL CExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetText();

	SetControl();

	return TRUE;
}

void CExampleDlg::OnOK()
{
	if (!Execute())
		return;

	CMyDialog::OnOK();
}

void CExampleDlg::SetText()
{
}

void CExampleDlg::SetControl()
{
	m_cobx.ResetContent();

	for (long indx = 0; indx < E_COBX_NUM; ++indx)
	{
		auto item = m_cobx.AddString(g_example_name[indx]);
		m_cobx.SetItemData(item, indx);
	}
	
	m_cobx.SetCurSel(0);
}

void CExampleDlg::Example()
{
	auto pMyPackage = m_pMyDoc->GetPackage();
	auto pModuleNode = std::static_pointer_cast<CModuleNode>(pMyPackage->GetModule(MYTYPE_NODE));

	// 조회
	std::vector<MYITR> aItr;
	pModuleNode->GetItrList(aItr);
	for (auto itr : aItr)
	{
		auto tNode = pModuleNode->GetAtNU(itr);
		auto pNode = ITR_TO_DATA(CEntityNode, itr);

		if (tNode.Key != pNode->Key)
		{
			ASSERT(g_warning);
		}
	}

	CTransaction tr(pMyPackage);
	if (!tr.Begin())
		return;

	// 추가
	CEntityNode tInsert;
	tInsert.Key = pModuleNode->GetNewKey();
	tInsert.aVertex = glm::vec3(0.f);
	tInsert.aNormal = glm::vec3(0.f);
	tInsert.aTexCord = glm::vec3(0.f);
	tInsert.aTangent = glm::vec3(0.f);
	tInsert.aBitangent = glm::vec3(0.f);

	auto itrNode = pModuleNode->InsertNU(tInsert);
	if (!ITR_IS_VALID(itrNode))
	{
		ASSERT(g_warning);

		tr.Rollback();
		return;
	}

	// 수정 
	auto tModify = pModuleNode->GetAtNU(itrNode);
	tModify.aVertex = glm::vec3(1.f);
	if (!pModuleNode->SetAtNU(itrNode, tModify))
	{
		ASSERT(g_warning);

		tr.Rollback();
		return;
	}

	// 삭제
	if (!pModuleNode->Remove(itrNode))
	{
		ASSERT(g_warning);

		tr.Rollback();
		return;
	}

	tr.Commit();
}

BOOL CExampleDlg::Execute()
{
	auto item = m_cobx.GetCurSel();
	auto itemData = m_cobx.GetItemData(item);

	switch (itemData)
	{
	case E_COBX_TEST:
		{
			MyTarget target;
			target.SetMyObject(1);

			auto pObject = target.GetMyObject();
			if (pObject != nullptr)
			{
				//pObject->GetTypeObject<MyObjectSteel>();
			}
		}
		break;
	case E_COBX_MESH_FACE:
		{
			ExecuteFace();
		}
		break;
	case E_COBX_MESH_BOX:
		{
			ExecuteBox();
		}
		break;
	case E_COBX_MODERN:
		{
			CModernExample example;
			example.Example();
		}
		break;
	default:
		{
			ASSERT(0);
		}
		break;
	}

	return TRUE;
}

void CExampleDlg::ExecuteFace()
{
	auto pMyPackage = m_pMyDoc->GetPackage();
	auto pModuleNode = std::static_pointer_cast<CModuleNode>(pMyPackage->GetModule(MYTYPE_NODE));
	auto pModuleElem = std::static_pointer_cast<CModuleElem>(pMyPackage->GetModule(MYTYPE_ELEM));
	auto pModuleMesh = std::static_pointer_cast<CModuleMesh>(pMyPackage->GetModule(MYTYPE_MESH));

	CTransaction tr(pMyPackage);
	if (!tr.Begin())
		return;

	// 추가
	CEntityNode tNode;
	tNode.Key = pModuleNode->GetNewKey();
	tNode.aVertex.x = -0.5f;
	tNode.aVertex.y = -0.5f;
	tNode.aNormal.z = 1.f;
	auto itrNodeLB = pModuleNode->InsertNU(tNode);
	
	tNode.Key = pModuleNode->GetNewKey();
	tNode.aVertex.x = 0.5f;
	tNode.aVertex.y = -0.5f;
	tNode.aNormal.z = 1.f;
	auto itrNodeRB = pModuleNode->InsertNU(tNode);

	tNode.Key = pModuleNode->GetNewKey();
	tNode.aVertex.x = 0.5f;
	tNode.aVertex.y = 0.5f;
	tNode.aNormal.z = 1.f;
	auto itrNodeRT = pModuleNode->InsertNU(tNode);

	tNode.Key = pModuleNode->GetNewKey();
	tNode.aVertex.x = -0.5f;
	tNode.aVertex.y = 0.5f;
	tNode.aNormal.z = 1.f;
	auto itrNodeLT = pModuleNode->InsertNU(tNode);

	CEntityElem tElemL;
	tElemL.Key = pModuleElem->GetNewKey();
	tElemL.uiType = E_ELEMTYPE_TRI3;
	tElemL.aItrNode.push_back(itrNodeLT);
	tElemL.aItrNode.push_back(itrNodeLB);
	tElemL.aItrNode.push_back(itrNodeRB);
	auto itrElemL = pModuleElem->InsertNU(tElemL);

	CEntityElem tElemR;
	tElemR.Key = pModuleElem->GetNewKey();
	tElemR.uiType = E_ELEMTYPE_TRI3;
	tElemR.aItrNode.push_back(itrNodeRB);
	tElemR.aItrNode.push_back(itrNodeRT);
	tElemR.aItrNode.push_back(itrNodeLT);
	auto itrElemR = pModuleElem->InsertNU(tElemR);

	CEntityMesh tMesh;
	tMesh.Key = pModuleMesh->GetNewKey();
	tMesh.aItrNode.push_back(itrNodeLB);
	tMesh.aItrNode.push_back(itrNodeRB);
	tMesh.aItrNode.push_back(itrNodeRT);
	tMesh.aItrNode.push_back(itrNodeLT);
	tMesh.aItrElem.push_back(itrElemL);
	tMesh.aItrElem.push_back(itrElemR);
	pModuleMesh->InsertNU(tMesh);

	if (!tr.Commit())
		ASSERT(g_warning);
}

void CExampleDlg::ExecuteBox()
{
	float g_vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	int g_tri_index[] = {
		1, 1, 2, 3,
		1, 4, 5, 6,

		1, 7, 8, 9,
		1, 10, 11, 12,

		1, 13, 14, 15,
		1, 16, 17, 18,

		1, 19, 20, 21,
		1, 22, 23, 24,

		1, 25, 26, 27,
		1, 28, 29, 30,

		1, 31, 32, 33,
		1, 34, 35, 36
	};

	auto pMyPackage = m_pMyDoc->GetPackage();
	auto pModuleNode = std::static_pointer_cast<CModuleNode>(pMyPackage->GetModule(MYTYPE_NODE));
	auto pModuleElem = std::static_pointer_cast<CModuleElem>(pMyPackage->GetModule(MYTYPE_ELEM));
	auto pModuleMesh = std::static_pointer_cast<CModuleMesh>(pMyPackage->GetModule(MYTYPE_MESH));

	CTransaction tr(pMyPackage);
	if (!tr.Begin())
		return;

	std::vector<MYITR> aItrNode;
	{
		auto SZ_POS = sizeof(float) * 3;
		auto SZ_NORMAL = sizeof(float) * 3;
		auto SZ_TEXCORD = sizeof(float) * 2;
		auto SZ_DATA = (SZ_POS + SZ_NORMAL + SZ_TEXCORD);
		auto szNum = sizeof(g_vertices) / SZ_DATA;
		for (auto indx = 0; indx < static_cast<int>(szNum); ++indx)
		{
			CEntityNode tNode;
			tNode.Key = pModuleNode->GetNewKey();
			tNode.aVertex = glm::vec3(g_vertices[indx * 8 + 0], g_vertices[indx * 8 + 1], g_vertices[indx * 8 + 2]);
			tNode.aNormal = glm::vec3(g_vertices[indx * 8 + 3], g_vertices[indx * 8 + 4], g_vertices[indx * 8 + 5]);
			tNode.aTexCord = glm::vec2(g_vertices[indx * 8 + 6], g_vertices[indx * 8 + 7]);

			auto itrNode = pModuleNode->InsertNU(tNode);
			aItrNode.push_back(itrNode);
		}
	}

	std::vector<MYITR> aItrElem;
	{
		auto SZ_DATA = sizeof(int) * 4;
		auto szNum = sizeof(g_tri_index) / SZ_DATA;
		for (auto indx = 0; indx < static_cast<int>(szNum); ++indx)
		{
			CEntityElem tElem;
			tElem.Key = pModuleElem->GetNewKey();
			tElem.uiType = E_ELEMTYPE_TRI3;

			for (auto lvtx = 0; lvtx < 3; ++lvtx)
			{
				auto nidx = g_tri_index[indx * 4 + 1 + lvtx] - 1;
				auto itr = aItrNode[nidx];
			
				tElem.aItrNode.push_back(itr);
			}

			auto itrElem = pModuleElem->InsertNU(tElem);
			aItrElem.push_back(itrElem);
		}
	}
	
	CEntityMesh tMesh;
	tMesh.Key = pModuleMesh->GetNewKey();
	tMesh.aItrNode = aItrNode;
	tMesh.aItrElem = aItrElem;
	pModuleMesh->InsertNU(tMesh);

	if (!tr.Commit())
		ASSERT(g_warning);
}

void CExampleDlg::OnClickedApply()
{
	Execute();
}
