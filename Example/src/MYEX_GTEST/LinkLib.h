#pragma once

#ifndef __LINK_MYEX_GTEST__
#define __LINK_MYEX_GTEST__
#define LINKNAME "MYEX_GTEST.lib"

#if !defined(_AFXDLL)
#error MFC Lib를 Shared Lib로 지정해야 합니다 !
#endif

#if (_MSC_VER == 1200)
#error vs6.0
#elif (_MSC_VER == 1400)
#error vs2005(8.0)
#elif (_MSC_VER == 1500)
#error vs2008(9.0)
#elif (_MSC_VER == 1600)
#error vs2010(10.0)
#elif (_MSC_VER == 1700)
#error vs2012(11.0)
#elif (_MSC_VER == 1800)
#error vs2013(12.0)
#elif (_MSC_VER == 1900)
#error vs2015(14.0)
#elif (_MSC_VER >= 1910 && _MSC_VER <= 1916) // vs2017(15.0)
	#ifndef _X64
		#if defined(_DEBUG)
			#define AUTOLIBNAME "..\\..\\lib\\v141\\Debug\\x86\\" LINKNAME
		#else
			#define AUTOLIBNAME "..\\..\\lib\\v141\\Release\\x86\\" LINKNAME
		#endif
	#else
		#if defined(_DEBUG)
			#define AUTOLIBNAME "..\\..\\lib\\v141\\Debug\\x64\\" LINKNAME
		#else
			#define AUTOLIBNAME "..\\..\\lib\\v141\\Release\\x64\\" LINKNAME
		#endif
	#endif
#endif

#pragma message( "automatically link with (" AUTOLIBNAME ")")
#pragma comment(lib, AUTOLIBNAME)
#undef AUTOLIBNAME
#undef LINKNAME
#endif // End of __LINK_MYEX_DLG__