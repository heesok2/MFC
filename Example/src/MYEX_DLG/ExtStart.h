#pragma once

#ifdef __EXT_DLL__
#error Extension Dll Error
#endif

#define __EXT_DLL__

#ifdef __MYEX_DLG__
	#define __MY_EXT_CLASS__	__declspec(dllexport)
	#define __MY_EXT_API__		extern "C" __declspec(dllexport)
#else
	#define __MY_EXT_CLASS__	__declspec(dllimport)
	#define __MY_EXT_API__		extern "C" __declspec(dllimport)
#endif

