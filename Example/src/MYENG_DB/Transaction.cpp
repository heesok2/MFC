#include "pch.h"
#include "Transaction.h"

using namespace mydb;

CTransaction::CTransaction(std::shared_ptr<mydb::CPackage> pPackage)
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
	return TRUE;
}

void CTransaction::Rollback()
{
}