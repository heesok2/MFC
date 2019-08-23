#include "stdafx.h"
#include "BFBaseMessage.h"
#include "BFBaseMsgParser.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseMessage* CBFBaseMessage::GetInstance()
{
	static CBFBaseMessage instance;
	return &instance;
}

CBFBaseMessage::CBFBaseMessage(void)
	: m_eType( LANG_US )
{
}

CBFBaseMessage::~CBFBaseMessage(void)
{
}

void CBFBaseMessage::SetChangedLanguage(LANG_TYPE eType)
{
	if( m_eType == eType ) return;

	CBFBaseMsgParser parser;

	parser.Load( _T("D:\\BaseFrame\\bin\\Language\\KR\\BFP_MAIN.ini") );

}