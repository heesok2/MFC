#pragma once

#ifndef GLOBAL_DEF
#define GLOBAL_DEF

static int g_warning = 0;

#define MYTYPE UINT
#define MYKEY UINT 
#define MYITR DWORD_PTR 
#define VPTR_SIZE sizeof(DWORD_PTR) // Virtual method table size

#define ITR_IS_VALID(x) ((x) > 0)
#define KEY_IS_VALID(x) ((x) > 0)
#define _SAFE_DELETE(x) { if(x){delete (x);(x)=NULL; }}
#define _SAFE_DELETE_ARRAY(x) { if(x){delete[] (x); (x)=NULL;} }

#endif // !GLOBAL_DEF
