#include "stdafx.h"

CAcceptor* CAcceptor::CreateAcceptor(unsigned int nId, CReactor* pReactor, evutil_socket_t fd)
{
	CAcceptor* pAcceptor = new CAcceptor(nId, pReactor);
	if (pAcceptor->Init(fd))
	{
		return pAcceptor;
	}
	else
	{
		//底层出问题了
		delete pAcceptor;
		return NULL;
	}
	
}

CAcceptor::CAcceptor(unsigned int nId, CReactor* pReactor) : CBufferEvent(nId, pReactor), m_eState(eUnConnected)
{
	
}

bool CAcceptor::Init(evutil_socket_t fd)
{
	if (m_eState == eConnected)
	{
		return false;
	}

	m_pBev = bufferevent_socket_new(m_pReactor->GetEventBase(), fd, BEV_OPT_CLOSE_ON_FREE);
	if (!m_pBev) {
		event_base_loopbreak(m_pReactor->GetEventBase());
		return false;
	}

	m_pReactor->RegisteReactorHandle(this);

	m_eState = eConnected;

	return true;
}

void CAcceptor::ShutDown()
{
	if (m_eState != eUnConnected)
	{
		CBufferEvent::ShutDown();
		m_eState = eUnConnected;
	}
}




