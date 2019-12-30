// MYPLUG_GTEST.h : MYPLUG_GTEST DLL의 주 헤더 파일
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 주 기호입니다.


// CMYPLUGGTESTApp
// 이 클래스 구현에 대해서는 MYPLUG_GTEST.cpp를 참조하세요.
//

class CMYPLUGGTESTApp : public CWinApp
{
public:
	CMYPLUGGTESTApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
