#include "stdafx.h"
#include "Package.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace mydb;

CPackage::CPackage()
{
}

CPackage::~CPackage()
{
}


std::shared_ptr<CModule> CPackage::GetModule(MYTYPE _type)
{
	auto itr = m_mSeqIndex.find(_type);
	if (itr == m_mSeqIndex.end())
	{
		ASSERT(0);
		return nullptr;
	}

	return m_aModule[itr->second];
}