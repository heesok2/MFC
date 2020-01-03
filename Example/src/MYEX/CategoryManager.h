#pragma once

class CCategoryBase;
class CCategoryManager
{
public:
	CCategoryManager();
	virtual ~CCategoryManager();

public:
	void SetMenu(CMFCRibbonBar* pRibbonBar);

private:
	std::map<UINT, std::shared_ptr<CCategoryBase>> m_mCategory;

};

