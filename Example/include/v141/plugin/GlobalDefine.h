#pragma once

#ifndef GLOBAL_DEF
#define GLOBAL_DEF

static int g_warning = 0;

#define ETYPE UINT // Entity Type
#define EKEY UINT // Entity Key

#define _SAFE_DEL(x) { if(x) { delete (x); } (x) = nullptr; }

#endif // !GLOBAL_DEF
