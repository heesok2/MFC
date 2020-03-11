#pragma once

class CTemplateExample
{
};

class CAliasExample
{

};

template <typename T>
class CAliasTemplate
{

};

extern int FuncInt(std::shared_ptr<CTemplateExample>);
extern double FuncDouble(std::unique_ptr<CTemplateExample>);
extern bool FuncBool(CTemplateExample*);

extern void TemplateExample();
extern void AliasExample();

