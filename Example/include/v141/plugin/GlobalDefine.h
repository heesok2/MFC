#pragma once

#ifndef GLOBAL_DEF
#define GLOBAL_DEF

static int g_warning = 0;

#define MYTYPE UINT
#define MYKEY UINT 
#define MYITR DWORD_PTR 
#define VPTR_SIZE sizeof(DWORD_PTR) // Virtual method table

#define _SAFE_DEL(x) { if(x) { delete (x); } (x) = nullptr; }

#endif // !GLOBAL_DEF
