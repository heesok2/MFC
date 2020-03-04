#pragma once

#include <memory>

#include "MyObjectDefine.h"
#include "MyObject.h"

class AFX_EXT_CLASS MyTarget
{
public:
	MyTarget(IDBSession* pDBSession = nullptr)
		: m_pDBSession(pDBSession) {}
	virtual ~MyTarget() = default;

public:
	const MyObject* GetMyObject() const;
	void SetMyObject(MIterator itrObject);	

private:
	IDBSession* m_pDBSession;
	std::unique_ptr<MyObject> m_pObject;
};