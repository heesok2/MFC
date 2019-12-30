#pragma once

namespace mydb
{
	class AFX_EXT_CLASS CEntity
	{
	public:
		CEntity();
		virtual ~CEntity();

	public:
		virtual const MYKEY GetKey() const
		{
			return *((MYKEY*)(((BYTE*)this) + VPTR_SIZE));
		}

	};
}
