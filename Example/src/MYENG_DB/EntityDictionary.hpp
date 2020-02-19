#pragma once

#ifndef DEF_ENTITYDICT
#define DEF_ENTITYDICT

#include "DataBaseDefine.h"

#define D_DEFAULT_HASH_NUM 10000
#define D_HASH_INDEX(key, hash_size) ((key) % (hash_size))

template <class ENTITY_DATA>
class CEntityDictionary
{
public:
	typedef struct tagEntity
	{
		TEntityParam Param;
		ENTITY_DATA Data;

		// Linked List
		tagEntity* pPrevD;
		tagEntity* pNextD;

		// Hashmap List
		tagEntity* pPrevH;
		tagEntity* pNextH;

	} TEntity, *LPEntity;

public:
	CEntityDictionary(long lHashNum = D_DEFAULT_HASH_NUM) 
		: m_max(0)
		, m_lDataNum(0), m_pHead(nullptr), m_pTail(nullptr)
		, m_lHashNum(lHashNum), m_pHashmap(nullptr)
	{
		if (m_lHashNum < D_DEFAULT_HASH_NUM) 
			m_lHashNum = D_DEFAULT_HASH_NUM;

		m_pHashmap = new LPEntity[m_lHashNum];
		memset(m_pHashmap, 0, sizeof(LPEntity)*m_lHashNum);
	}

	~CEntityDictionary()
	{
		DeleteAll();

		DeleteHashAll();
	}

public:
	void Clear()
	{
		DeleteAll();
	}

	BOOL IsEmpty()
	{
		return m_lDataNum == 0;
	}

	long GetSize()
	{
		return m_lDataNum;
	}

	MYKEY GetNewKey() { return m_max + 1; }

	MYITR Find(MYKEY myKey)
	{
		if (!KEY_IS_VALID(myKey))
		{
			ASSERT(g_warning);
			return (MYITR)nullptr;
		}

		auto idxH = D_HASH_INDEX(myKey, m_lHashNum);
		auto pEntity = m_pHashmap[idxH];
		while (pEntity != nullptr)
		{
			if (pEntity->Data.GetKey() == myKey)
				return (MYITR)pEntity;

			pEntity = pEntity->pNextH;
		}

		return (MYITR)nullptr;
	}

	MYITR InsertNU(const ENTITY_DATA& data)
	{
		auto dbKey = data.GetKey();
		auto itr = Find(dbKey);

		if (ITR_IS_VALID(itr))
		{
			ASSERT(g_warning);
			return (MYITR)nullptr;
		}

		auto pEntity = new TEntity();
		pEntity->Data = data;

		InsertData(pEntity);
		InsertHash(pEntity);

		SetMaxKey(dbKey);

		return (MYITR)pEntity;
	}

	BOOL SetAtNU(MYITR itr, const ENTITY_DATA& data)
	{
		auto dbKey = data.GetKey();
		auto itrFind = Find(dbKey);

		if (!ITR_IS_VALID(itrFind) || itrFind != itr)
		{
			ASSERT(g_warning);
			return FALSE;
		}

		auto pEntity = (LPEntity)itr;

		RemoveHash(pEntity);
		pEntity->Data = data;
		InsertHash(pEntity);

		SetMaxKey(dbKey);

		return TRUE;
	}

	BOOL Remove(MYITR itr)
	{
		if (!ITR_IS_VALID(itr))
		{
			ASSERT(g_warning);
			return FALSE;
		}

		auto pEntity = (LPEntity)itr;

		RemoveHash(pEntity);
		RemoveData(pEntity);

		return TRUE;
	}

	const ENTITY_DATA& GetAtNU(MYITR itr) const
	{
		return ((LPEntity)itr)->Data;
	}

	long GetList(std::vector<MYITR>& aItr)
	{
		auto pEntity = m_pHead;
		while (pEntity != nullptr)
		{
			aItr.push_back((MYITR)pEntity);
			pEntity = pEntity->pNextD;
		}

		return static_cast<long>(aItr.size());
	}

	long GetListData(std::vector<ENTITY_DATA>& aData)
	{
		auto pEntity = m_pHead;
		while (pEntity != nullptr)
		{
			aData.push_back(pEntity->Data);
			pEntity = pEntity->pNextD;
		}

		return static_cast<long>(aData.size());
	}

protected:
	void DeleteAll()
	{
		auto pEntity = m_pHead;
		auto pNext = m_pHead;
		while (pEntity != nullptr)
		{
			pNext = pEntity->pNextD;
			_SAFE_DELETE(pEntity);
			pEntity = pNext;
		}

		m_max = 0;

		m_lDataNum = 0;
		m_pHead = nullptr;
		m_pTail = nullptr;

		memset(m_pHashmap, 0, sizeof(LPEntity)*m_lHashNum);
	}

	void DeleteHashAll()
	{
		_SAFE_DELETE_ARRAY(m_pHashmap);

		m_lHashNum = 0;
	}

	void InsertData(TEntity* pEntity)
	{
		if (m_pHead == nullptr)
		{
			pEntity->pPrevD = nullptr;
			pEntity->pNextD = nullptr;

			m_pHead = m_pTail = pEntity;
		}
		else
		{
			pEntity->pPrevD = m_pTail;
			pEntity->pNextD = nullptr;

			if (m_pTail != nullptr)
				m_pTail->pNextD = pEntity;

			m_pTail = pEntity;
		}

		m_lDataNum++;
	}

	void RemoveData(TEntity* pEntity)
	{
		if (pEntity->pPrevD) pEntity->pPrevD->pNextD = pEntity->pNextD;
		else m_pHead = pEntity->pNextD;

		if (pEntity->pNextD) pEntity->pNextD->pPrevD = pEntity->pPrevD;
		else m_pTail = pEntity->pPrevD;

		_SAFE_DELETE(pEntity);

		m_lDataNum--;
	}

	void InsertHash(TEntity* pEntity)
	{
		auto dbKey = pEntity->Data.GetKey();

		auto hidx = D_HASH_INDEX(dbKey, m_lHashNum);
		auto pHmap = m_pHashmap[hidx];

		pEntity->pPrevH = nullptr;
		pEntity->pNextH = pHmap;
		if (pHmap != nullptr)
			pHmap->pPrevH = pEntity;

		m_pHashmap[hidx] = pEntity;
	}

	void RemoveHash(TEntity* pEntity)
	{
		auto dbKey = pEntity->Data.GetKey();

		long hidx = D_HASH_INDEX(dbKey, m_lHashNum);
		auto pHash = m_pHashmap[hidx];

		if (pHash->pPrevH == nullptr)
			m_pHashmap[hidx] = pHash->pNextH;
		else
			pHash->pPrevH->pNextH = pHash->pNextH;

		if (pHash->pNextH != nullptr)
			pHash->pNextH->pPrevH = pHash->pPrevH;
	}

	void SetMaxKey(MYKEY myKey)
	{
		if (m_lDataNum == 0)
		{
			m_max = myKey;
		}
		else
		{
			m_max = myKey < m_max ? m_max : myKey;
		}
	}

protected:
	MYKEY m_max;

	long m_lDataNum;
	LPEntity m_pHead;
	LPEntity m_pTail;

	long m_lHashNum;
	LPEntity* m_pHashmap;
};

#endif // !DEF_ENTITYDICT

