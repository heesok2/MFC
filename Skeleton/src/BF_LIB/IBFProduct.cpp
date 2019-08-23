#include "stdafx.h"
#include "IBFProduct.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IBFProduct* IBFProduct::m_pInstance = nullptr;

IBFProduct::IBFProduct(void)
{
	ASSERT( m_pInstance == nullptr );

	if( m_pInstance == nullptr ) 
		m_pInstance = this; // 최초 Instance만 설정
}

IBFProduct::~IBFProduct(void)
{
}