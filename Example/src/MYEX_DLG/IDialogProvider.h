#pragma once

class CDocBase;
class IDialogProvider
{
public:
	static IDialogProvider* Instance();

public:
	IDialogProvider() {}
	~IDialogProvider() {}

public:
	BOOL ReqDialog(CDocBase* pDoc);
};

