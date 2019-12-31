#include "pch.h"
#include "Resource.h"
#include "ExampleDlg.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\Package.h"
#include "..\MYENG_DB\ModuleNode.h"

using namespace mydb;

CExampleDlg::CExampleDlg(CDocBase * pDoc, CWnd * pParent)
	: CMYDialog(CExampleDlg::IDD, pDoc, pParent)
{
}

CExampleDlg::~CExampleDlg()
{
}

void CExampleDlg::DoDataExchange(CDataExchange * pDX)
{
	CMYDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CExampleDlg, CDialog)

END_MESSAGE_MAP();

BOOL CExampleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetText();

	SetControl();

	// Example

	ExampleDB();

	return TRUE;
}

void CExampleDlg::SetText()
{
}

void CExampleDlg::SetControl()
{
}

void CExampleDlg::ExampleDB()
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
