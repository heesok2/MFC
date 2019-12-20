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

	protected:
		std::map<MYTYPE, std::shared_ptr<CModule>> m_mModule;

	};
}
