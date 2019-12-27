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

MYPOS CPackage::GetHeader()
{
	return m_mSeqIndex.begin();
}

MYPOS CPackage::GetEnd()
{
	return m_mSeqIndex.end();
}

void mydb::CPackage::Next(MYPOS & pos)
{
	pos++;
}

std::shared_ptr<CModule> CPackage::Get(MYPOS pos)
{
	return m_aModule[pos->second];
}

std::shared_ptr<CModule> CPackage::GetNext(MYPOS& pos)
{
	auto seq = pos->second;
	pos++;

	return m_aModule[seq];
}

std::shared_ptr<CModule> CPackage::GetModule(MYTYPE type)
{
	auto itr = m_mSeqIndex.find(type);
	if (itr == m_mSeqIndex.end())
	{
		ASSERT(0);
		return nullptr;
	}

	return m_aModule[itr->second];
}

