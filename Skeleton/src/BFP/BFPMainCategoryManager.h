#pragma once

#include <map>

class CBFPMainCategoryBase;
class CBFPMainCategoryManager
{
	enum CATEGORY_TYPE 
	{
		CT_SAMPLE = 0,
		CT_SAMPLE2,
		CT_NUM
	};

public:
	CBFPMainCategoryManager(void);
	virtual ~CBFPMainCategoryManager(void);

public:
	void SetMenu( CMFCRibbonBar* pRibbonBar );

private:
	std::map<UINT, CBFPMainCategoryBase*> m_mapCategory;

};