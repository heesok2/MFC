#include "stdafx.h"
#include "MyPackage.h"

#include "..\MYENG_BASE\DocBase.h"
#include "..\MYENG_DB\ModuleNode.h"
#include "..\MYENG_DB\ModuleElem.h"
#include "..\MYENG_DB\ModuleMesh.h"

CMyPackage::CMyPackage(CDocBase* pDoc)
	: CPackage(pDoc)
{
}

CMyPackage::~CMyPackage()
{
}

void CMyPackage::CreateModule()
{
	auto lambda_module = [&](auto pModule)
	{
#ifdef DEBUG
		auto itr = m_mSeqIndex.find(pModule->GetType());
		if (itr != m_mSeqIndex.end())
		{
			ASSERT(g_warning);
		}
#endif // DEBUG

		auto mytype = pModule->GetType();
		auto mySeq = static_cast<UINT>(m_aModule.size());

		m_aModule.push_back(pModule);
		m_mSeqIndex.insert(std::pair<MYTYPE, UINT>(mytype, mySeq));
	};

	// DB Relation 에 맞게 저장해야 한다.
	lambda_module(std::make_shared<CModuleNode>(this));
	lambda_module(std::make_shared<CModuleElem>(this));
	lambda_module(std::make_shared<CModuleMesh>(this));

}
