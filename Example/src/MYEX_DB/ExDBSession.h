#pragma once

#include "ExData.h"
class AFX_EXT_CLASS CExDBSession
{
public:
	CExDBSession();
	virtual ~CExDBSession();

public:
	std::vector<std::shared_ptr<CExData>> m_aData;
};