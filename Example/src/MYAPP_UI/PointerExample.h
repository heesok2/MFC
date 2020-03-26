#pragma once
#include <memory>

class CPointerExample
{
};

class CUniqueExample : public CPointerExample
{

};

template<typename T>
extern void TemplateArgs(T value);

template<typename T, typename ...Args>
extern void TemplateArgs(T value, Args && ...args);

extern void PointerExample();
