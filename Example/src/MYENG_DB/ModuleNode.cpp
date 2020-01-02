#include "pch.h"
#include "ModuleNode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CModuleNode::CModuleNode(mydb::CPackage* pPackage)
	: CModuleData<CEntityNode>(pPackage)
{

}

CModuleNode::~CModuleNode()
{

}