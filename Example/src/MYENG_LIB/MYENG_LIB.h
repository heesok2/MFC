// MYENG_LIB.h : MYENG_LIB DLL의 주 헤더 파일
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 주 기호입니다.


// CMYENGLIBApp
// 이 클래스 구현에 대해서는 MYENG_LIB.cpp를 참조하세요.
//

class CMYENGLIBApp : public CWinApp
{
public:
	CMYENGLIBApp();

// 재정의입니다.
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
