#pragma once

#ifndef D_DOUBLENUM
#define D_DOUBLENUM

extern "C" __declspec(dllexport) int doubleNum(int x)
{
	return x * 2;
}

#endif // D_DOUBLENUM
