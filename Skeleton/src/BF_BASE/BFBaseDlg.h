#pragma once

#include "BF_BASERes.h"

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CBFBaseDlg : public CDialog
{
public:
	CBFBaseDlg(void);
	virtual ~CBFBaseDlg(void);

	enum { IDD = IDD_BFPBASE_DLG };

public:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

};
#include "HeaderPost.h"