#include "stdafx.h"
#include "MYPackage.h"

#include "..\MYENG_DB\ModuleNode.h"

CMYPackage::CMYPackage()
{
}

CMYPackage::~CMYPackage()
{
}

void CMYPackage::CreateModule()
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

}
