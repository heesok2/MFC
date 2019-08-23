#include "stdafx.h"
#include "BFBaseMsgParser.h"

#include <fstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBFBaseMsgParser::CBFBaseMsgParser(void)
{
}

CBFBaseMsgParser::~CBFBaseMsgParser(void)
{
}

void CBFBaseMsgParser::LoadMsg(LANG_TYPE eType)
{
	MAP_LENG mPrev = m_mLeng;


	switch( eType )
	{
	case LANG_US:
		{

		}
		break;
	case LANG_KR:
		{

		}
		break;
	default:
		break;
	}
}

void CBFBaseMsgParser::Load(CString strPath)
{
	std::wifstream wfs( strPath );
	if( !wfs.is_open() ) 
		return;

	CString strMsg;
	std::wstring strBuf;
	while( std::getline( wfs, strBuf) )
	{
		strMsg = strBuf.c_str();
		strMsg.Trim();

		if( strMsg.IsEmpty() ) continue;
		if( strMsg.GetAt(0) == ';' ) continue;
		
		int nItem = strMsg.Find( _T("=") );
		if( nItem == -1 ) continue;

		CString strID = strMsg.Left( nItem );
		CString strVal = strMsg.Right( strMsg.GetLength() - (nItem+1) ); // '=' 문자를 제거하기 위해서
		
		int nItemID = strID.Find( _T("/**/") );
		int nItemValBeg = strVal.Find( '\"' );
		int nItemValEnd = strVal.ReverseFind( '\"' );

		if( nItemValBeg == -1 || nItemValEnd == -1  ) continue;
		if( nItemValBeg >= nItemValEnd ) continue;
		if( nItemID == -1 )
		{
			int nFind = strID.FindOneOf( _T("/**/") );
			if( nFind != -1 ) continue;
		}

		if( nItemID != -1 )
		{
			strID = strID.Right( strID.GetLength() - CString(_T("/**/")).GetLength() );
		}

		{
			nItemValBeg += 1; // '\"' 문자를 제거하기 위해서 
			strVal = strVal.Mid( nItemValBeg, nItemValEnd-nItemValBeg );
		}

		auto itr = m_mapMsg.find( strID );
		if( itr != m_mapMsg.end() ) ASSERT(0);

		m_mapMsg.insert( std::pair<CString, CString>(strID, strVal) );
	}

	wfs.close();
}
