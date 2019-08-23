#pragma once

#define D_PRODUCT_NAME				_T("Base Frame")
#define D_PRODUCT_NAME_ONLY			_T("Base Frame")
#define D_MODEL_FILE_FILTER			_T("Base Frame Files(*.bfp)|*.bfp|All File(*.*)|*.*||")
#define D_MODEL_FILE_EXT			_T(".bfp")
#define D_TEXT_FILE_FILTER			_T("Base Frame Files(*.bfp)|*.bfp|All File(*.*)|*.*||")
#define D_TEXT_FILE_EXT				_T(".bfp")

#define D_PROG_ALL		0xFFFFFFF
#define D_PROG_BFP		0x0000001	// Base Frame Program

#ifndef D_PGM_VER
#define D_PGM_VER(n1,n2,n3,n4) ((n1<<24)+(n2<<16)+(n3<<8)+n4)
#endif

#define D_PRODUCT_VERSION				100
#define D_PRODUCT_BUILD_NO				1
#define D_PRODUCT_VERSION_STR			_T("1.0.0")
#define D_PRODUCT_VERSION_TITLE_STR		_T("2018")
#define D_PRODUCT_VERSION_CODE			D_PGM_VER(1,0,0,1)