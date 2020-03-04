#include "pch.h"
#include "MyObject.h"

MyObjectGKey::MyObjectGKey(IDBSession * pDBSession, MIterator itr)
	: MyObject(pDBSession, itr)
{
	if (ITR_TO_DATATYPE(itr) == DATATYPE_STEEL)
		m_pChild = std::make_unique<MyObjectSteel>(pDBSession, itr);
	else if (ITR_TO_DATATYPE(itr) == DATATYPE_CONCRETE)
		m_pChild = std::make_unique<MyObjectConcrete>(pDBSession, itr);
	else 
		m_pChild = std::make_unique<MyObjectFeature>(pDBSession, itr);
}
