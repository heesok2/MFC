#pragma once

#include "Transaction.h"

namespace mydb
{
#ifndef DEF_MYPOS
#define DEF_MYPOS

	typedef std::map<MYTYPE, UINT>::iterator MYPOS;

#endif // !DEF_MYPOS


	class CModule;
	class AFX_EXT_CLASS CPackage
	{
	public:
		CPackage(CDocument* pDoc);
		virtual ~CPackage();

	public:
		virtual void CreateModule() = 0;
				
	public:
		CDocument* GetDocument() { return m_pMyDoc; }

	public:
		MYPOS GetHeader();
		MYPOS GetEnd();
		void Next(MYPOS& pos);
		std::shared_ptr<CModule> Get(MYPOS pos);
		std::shared_ptr<CModule> GetNext(MYPOS& pos);		
		std::shared_ptr<CModule> GetModule(MYTYPE type);

	protected:
		CDocument* m_pMyDoc;

		std::map<MYTYPE, UINT> m_mSeqIndex;
		std::vector<std::shared_ptr<CModule>> m_aModule;

	};
}
