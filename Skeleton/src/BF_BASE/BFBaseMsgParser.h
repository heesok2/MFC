#pragma once

#include "BFBaseMessageDef.h"

#include <map>
#include <vector>

class CBFBaseMsgParser
{
	typedef std::vector<CString> VEC_PATH;
	typedef std::map<CString, CString> MAP_LENG;

public:
	CBFBaseMsgParser(void);
	virtual ~CBFBaseMsgParser(void);

public:
	void LoadMsg( LANG_TYPE eType );
	void Load( CString strPath );

private:
	VEC_PATH m_vPath;
	MAP_LENG m_mLeng;

	std::vector<CString> m_vMsgPath;
	std::map<CString, CString> m_mapMsg;
};