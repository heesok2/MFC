#include "pch.h"
#include "Transaction.h"
#include "Package.h"

#include "..\MYENG_LIB\NotifyDefine.h"

using namespace mydb;

CTransaction::CTransaction(std::shared_ptr<mydb::CPackage> pPackage)
	: m_pMyPackage(pPackage)
{
}

CTransaction::~CTransaction()
{
}

BOOL CTransaction::Begin()
{
	return TRUE;
}

BOOL CTransaction::Commit()
{
	m_pMyPackage->GetDocument()->UpdateAllViews(nullptr, E_DOCUMENT_DB_UPDATE);

	return TRUE;
}

void CTransaction::Rollback()
{
}