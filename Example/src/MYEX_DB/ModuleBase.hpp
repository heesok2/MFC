#pragma once

#ifndef MODULEDATA_DEF
#define MODULEDATA_DEF

#include "Module.h"
#include "EntityDictionary.hpp"

namespace mydb
{
	template <class TD>
	class CModuleData : public mydb::CModule
	{
	public:
		CModuleData(CPackage * pPackage)
			: CModule(pPackage)
		{}
		virtual ~CModuleData() {}

	public: // Data 
		virtual void Clear()
		{
			m_Dictionary.Clear();
		}

		virtual BOOL Empty()
		{
			return m_Dictionary.IsEmpty();
		}

		virtual BOOL Exist(MYKEY key)
		{
			auto itr = m_Dictionary.Find(key);
			return ITR_IS_VALID(itr);
		}

		virtual MYITR Find(MYKEY key)
		{
			return m_Dictionary.Find(key);
		}

		virtual BOOL Find(MYKEY key, TD& data)
		{
			auto itr = m_Dictionary.Find(key);
			if (!ITR_IS_VALID(itr)) return FALSE;

			data = m_Dictionary.GetAtNU(itr);
			return TRUE;
		}

		virtual MYITR InsertNU(const TD& data)
		{
			return m_Dictionary.InsertNU(data);
		}

		virtual BOOL SetAtNU(MYITR itr, const TD& data)
		{
			return m_Dictionary.SetAtNU(itr, data);
		}

		virtual BOOL Remove(MYITR itr)
		{
			return m_Dictionary.Remove(itr);
		}

		virtual const TD& GetAtNU(MYITR itr) const
		{
			return m_Dictionary.GetAtNU(itr);
		}

		virtual long GetItrList(std::vector<MYITR>& lstItr)
		{
			return m_Dictionary.GetList(lstItr);
		}

		virtual long GetDataList(std::vector<TD>& lstData)
		{
			return m_Dictionary.GetListData(lstData);
		}

		virtual MYKEY GetNewKey()
		{
			return m_Dictionary.GetNewKey();
		}

	public:
		virtual MYITR GetDefaultData()
		{
			ASSERT(g_warning);
			return (MYITR)nullptr;
		}

		virtual void SetDefaultData()
		{
			ASSERT(g_warning);
		}

	protected:
		CEntityDictionary<TD> m_Dictionary;

	};
}

#endif // !MODULEDATA_DEF

