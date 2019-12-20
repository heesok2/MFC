#pragma once

class CDocBase;
class AFX_EXT_CLASS CAppDialogProvider
{
public:
	CAppDialogProvider();
	~CAppDialogProvider();

public:
	static INT_PTR DoModal(CDocBase* pDoc, LPCTSTR lpDialogName, LPVOID lpParam = nullptr);


};

