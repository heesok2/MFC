﻿// MYAPP_UI.h : MYAPP_UI DLL의 주 헤더 파일
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 주 기호입니다.


// CMYAPPUIApp
// 이 클래스 구현에 대해서는 MYAPP_UI.cpp를 참조하세요.
//

class CMYAPPUIApp : public CWinApp
{
public:
	CMYAPPUIApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
