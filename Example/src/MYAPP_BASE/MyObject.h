#pragma once

#include "MyObjectDefine.h"

class AFX_EXT_CLASS MyObject
{
public:
	MyObject(IDBSession* pDBSession, MIterator itr)
		: m_pDBSession(pDBSession)
		, m_itr(itr)
		, m_pChild(nullptr) 
	{}
	virtual ~MyObject() = default;

public:
	MIterator GetIterator() const { return m_itr; }
	const MyObject* GetChild() const { return m_pChild != nullptr ? m_pChild->GetChild() : this; }

	template<class T>
	const T* GetTypeObject() { return std::static_cast<T* const>(std::const_cast<GetChild()); }
	
protected:
	IDBSession* m_pDBSession;
	MIterator m_itr;

	std::unique_ptr<MyObject> m_pChild;
};

class AFX_EXT_CLASS MyObjectGKey : public MyObject
{
public:
	MyObjectGKey(IDBSession* pDBSession, MIterator itr);
	virtual ~MyObjectGKey() = default;


};

class AFX_EXT_CLASS MyObjectSteel : public MyObject
{
public:
	MyObjectSteel(IDBSession* pDBSession, MIterator itr)
		: MyObject(pDBSession, itr)
	{}
	virtual ~MyObjectSteel() = default;

};

class AFX_EXT_CLASS MyObjectConcrete : public MyObject
{
public:
	MyObjectConcrete(IDBSession* pDBSession, MIterator itr)
		: MyObject(pDBSession, itr)
	{}
	virtual ~MyObjectConcrete() = default;

};

class MyObjectFeature : public MyObject
{
public:
	MyObjectFeature(IDBSession* pDBSession, MIterator itr)
		: MyObject(pDBSession, itr)
	{}
	virtual ~MyObjectFeature() = default;

};
