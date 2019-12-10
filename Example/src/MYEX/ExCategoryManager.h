#pragma once

class CExCategoryBase;
class CExCategoryManager
{
public:
	CExCategoryManager();
	virtual ~CExCategoryManager();

public:
	void SetMenu(CMFCRibbonBar* pRibbonBar);

private:
	std::map<UINT, std::shared_ptr<CExCategoryBase>> m_mCategory;

};

