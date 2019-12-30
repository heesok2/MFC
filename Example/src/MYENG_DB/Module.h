#pragma once

namespace mydb
{
	class CPackage;
	class AFX_EXT_CLASS CModule
	{
	public:
		CModule(CPackage* pPackage);
		virtual ~CModule();

	public:
		virtual MYTYPE GetType() = 0;

	protected:
		CPackage* m_pPackage;

	};
}
