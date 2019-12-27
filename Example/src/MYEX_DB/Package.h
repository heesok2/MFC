#pragma once

namespace mydb
{
#ifndef DEF_MY_SEQ
#define DEF_MY_SEQ

	typedef std::map<MYTYPE, UINT>::iterator MYPOS;

#endif // !DEF_MY_SEQ


	class CModule;
	class AFX_EXT_CLASS CPackage
	{
	public:
		CPackage();
		virtual ~CPackage();

	public:
		virtual void CreateModule() = 0;
		virtual std::shared_ptr<CModule> GetModule(MYTYPE _type);
		
		MYPOS GetHeader();
		MYPOS GetEnd();
		void Next(MYPOS& pos);
		std::shared_ptr<CModule> Get(MYPOS pos);
		std::shared_ptr<CModule> GetNext(MYPOS& pos);
		

	protected:
		std::map<MYTYPE, UINT> m_mSeqIndex;
		std::vector<std::shared_ptr<CModule>> m_aModule;

	};
}
