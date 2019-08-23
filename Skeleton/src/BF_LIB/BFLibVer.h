#ifndef __BF_LIB_VER_H__
#define __BF_LIB_VER_H__

#if !defined(_AFXDLL)
#error MFC Lib를 Shared Lib로 지정해야 합니다 !
#endif

#if !defined(_X64)
	#if defined(_DEBUG)
		#if defined(_AFXEXT)
			#define AUTOLIBNAME "..\\..\\lib\\debug\\x86\\BF_LIB.lib"
		#else
			#define AUTOLIBNAME "..\\..\\lib\\debug\\x86\\BF_LIB.lib"
		#endif
	#else
		#if defined(_AFXEXT)
			#define AUTOLIBNAME "..\\..\\lib\\release\\x86\\BF_LIB.lib"
		#else
			#define AUTOLIBNAME "..\\..\\lib\\release\\x86\\BF_LIB.lib"
		#endif
	#endif
#else
	#if defined(_DEBUG)
		#if defined(_AFXEXT)
			#define AUTOLIBNAME "..\\..\\lib\\debug\\x64\\BF_LIB.lib"
		#else
			#define AUTOLIBNAME "..\\..\\lib\\debug\\x64\\BF_LIB.lib"
		#endif
	#else
		#if defined(_AFXEXT)
			#define AUTOLIBNAME "..\\..\\lib\\release\\x64\\BF_LIB.lib"
		#else
			#define AUTOLIBNAME "..\\..\\lib\\release\\x64\\BF_LIB.lib"
		#endif
	#endif
#endif


// Perform autolink here:
#pragma message( "automatically link with (" AUTOLIBNAME ")")
#pragma comment(lib, AUTOLIBNAME)
#undef AUTOLIBNAME
#endif // End of __BF_LIB_VER_H__
