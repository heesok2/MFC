#pragma once

#include "..\MYEX_DB\ExData.h"

class AFX_EXT_CLASS CExDataDlg : public CExData
{
public:
	CExDataDlg();
	virtual ~CExDataDlg();

public:
	virtual double DoubleSq(double dNum);

};

