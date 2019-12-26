#pragma once

namespace mydb
{
	class CModule;
	class AFX_EXT_CLASS CPackage
	{
	public:
		CPackage();
		virtual ~CPackage();

	public:
		virtual void CreateModule() = 0;
		virtual std::shared_ptr<CModule> GetModule(MYTYPE _type);

	protected:
		std::map<MYTYPE, UINT> m_mSeqIndex;
		std::vector<std::shared_ptr<CModule>> m_aModule;

	};
}
