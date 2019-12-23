#include "stdafx.h"
#include "MYEXPackage.h"

#include "..\MYEX_DB\ModuleNode.h"

CMYEXPackage::CMYEXPackage()
{
}

CMYEXPackage::~CMYEXPackage()
{
}

void CMYEXPackage::CreateModule()
{
	auto lambda_module = [&](auto pModule)
	{
		m_mModule[pModule->GetType()] = pModule;
	};

	lambda_module(std::make_shared<CModuleNode>(this));
}
