#include "pch.h"
#include "MyTarget.h"

const MyObject * MyTarget::GetMyObject() const
{
	return m_pObject != nullptr ? m_pObject->GetChild() : nullptr;
}

void MyTarget::SetMyObject(MIterator itrObject)
{
	if (ITR_TO_DATATYPE(itrObject) == DATATYPE_GKEY)
	{
		m_pObject = std::make_unique<MyObjectGKey>(m_pDBSession, itrObject);
	}
	else
	{
		ASSERT(0);
	}
}