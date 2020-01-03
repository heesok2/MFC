#include "pch.h"
#include "Resource.h"
#include "ExampleDlg.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\ModuleNode.h"
#include "..\MYENG_DB\ModuleElem.h"
#include "..\MYENG_DB\ModuleMesh.h"

using namespace mydb;

enum E_EXAMPLE_COBX
{
	E_COBX_UNKNOWN = -1
	, E_COBX_MESH_FACE = 0
	, E_COBX_MESH_BOX

	, E_COBX_NUM
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
	CString aName[E_COBX_NUM] =
	{
		_T("Mesh - Face")		// E_COBX_MESH_FACE
		, _T("Mesh - Box")		// E_COBX_MESH_BOX
	};

	m_cobx.ResetContent();

	for (long indx = 0; indx < E_COBX_NUM; ++indx)
	{
		auto item = m_cobx.AddString(aName[indx]);
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
	default:
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
}

void CExampleDlg::OnClickedApply()
{
	Execute();
}
