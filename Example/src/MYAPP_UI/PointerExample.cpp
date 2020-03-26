#include "pch.h"
#include "PointerExample.h"

#pragma warning(disable:4100)

template<typename T>
void TemplateArgs(T value)
{
	TRACE1("sizeof...(%d) : ", 0);
	TRACE1("%g\n", value);
}

template<typename T, typename ...Args>
void TemplateArgs(T value, Args && ...args)
{
	auto lSize = sizeof...(args);
	TRACE1("sizeof...(%d) : ", lSize);
	TRACE1("%g\n", value);
}

void PointerExample()
{
	TemplateArgs(1, 2, 3, 4.5, _T("Test"));

	auto lambda_delunq = [](CUniqueExample* pUniq)
	{
		delete pUniq;
	};

	std::unique_ptr<CUniqueExample, decltype(lambda_delunq)> pUniq(new CUniqueExample, lambda_delunq);
}