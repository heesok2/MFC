#pragma once

namespace mydb
{
	class CPackage;
	class AFX_EXT_CLASS CTransaction
	{
	public:
		CTransaction(std::shared_ptr<mydb::CPackage> pPackage);
		~CTransaction();

	public:
		BOOL Begin();
		BOOL Commit();
		void Rollback();

	};
}
