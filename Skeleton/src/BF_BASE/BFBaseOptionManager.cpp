#include "stdafx.h"
#include "BFBaseOptionManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseOptionManager* CBFBaseOptionManager::GetInstance()
{
	static CBFBaseOptionManager instance;
	return &instance;
}

CBFBaseOptionManager::CBFBaseOptionManager(void)
	: m_bCheck( FALSE ), m_nFlag(0)
{
}


CBFBaseOptionManager::~CBFBaseOptionManager(void)
{
}
