#pragma once

#ifdef __EXT_DLL__
#error Extension Dll Error
#endif

#define __EXT_DLL__

#ifdef __MYEX_BASE__
	#define __MY_EXT_CLASS__	__declspec(dllexport)
	#define __MY_EXT_API__		__declspec(dllexport)
	#define __MY_EXT_DATA__		__declspec(dllexport)
#else
	#define __MY_EXT_CLASS__	__declspec(dllimport)
	#define __MY_EXT_API__		__declspec(dllimport)
	#define __MY_EXT_DATA__		__declspec(dllimport)
#endif

