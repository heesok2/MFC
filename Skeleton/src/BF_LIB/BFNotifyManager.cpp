#include "stdafx.h"
#include "BFNotifyManager.h"
#include "BFNotifyObserver.h"

CBFNotifyManager::CBFNotifyManager(void)
{
}

CBFNotifyManager::~CBFNotifyManager(void)
{
	ASSERT( m_vObserver.empty() );
	ClearObservers();
}

void CBFNotifyManager::ClearObservers()
{
	m_vObserver.clear();
}

void CBFNotifyManager::AttachObserver(CBFNotifyObserver* pObsv)
{
	if( pObsv == nullptr ) return;

	auto itr = std::find( m_vObserver.begin(), m_vObserver.end(), pObsv );
	if( itr == m_vObserver.end() )
		m_vObserver.push_back( pObsv );
}

void CBFNotifyManager::DettachObserver(CBFNotifyObserver* pObsv)
{
	if( pObsv == nullptr ) return;

	auto itr = std::find( m_vObserver.begin(), m_vObserver.end(), pObsv );
	if( itr != m_vObserver.end() )
		m_vObserver.erase( itr );
}

int CBFNotifyManager::Notify(UINT Msg, WPARAM wParam /*= NULL*/, LPARAM lParam /*= NULL */)
{
	for( auto pObsv : m_vObserver )
	{
		auto res = pObsv->UpdateObserver( Msg, wParam, lParam );
		if( res != 0 ) return res;
	}

	return 0;
}