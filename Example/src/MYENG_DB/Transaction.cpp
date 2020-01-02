#include "pch.h"
#include "Transaction.h"
#include "Package.h"

#include "..\MYENG_LIB\NotifyDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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