#include "stdafx.h"

CConnector::CConnector(unsigned int nId, CReactor* pReactor) : CBufferEvent(nId, pReactor), m_pDns(NULL), m_eState(eUnConnected)
{

}

CConnector* CConnector::CreateConnector(unsigned int nId, CReactor* pReactor)
{
	CConnector* pConnector = new CConnector(nId, pReactor);
	if (pConnector->Init())
	{
		return pConnector;
	}
	else
	{
		//底层出问题了
		delete pConnector;
		return NULL;
	}
}

bool CConnector::Init()
{
	if (m_eState == eConnected)
	{
		return false;
	}

	m_pBev = bufferevent_socket_new(m_pReactor->GetEventBase(), -1, BEV_OPT_CLOSE_ON_FREE);
	if (!m_pBev) {
		event_base_loopbreak(m_pReactor->GetEventBase());
		return false;
	}

	m_pReactor->RegisteReactorHandle(this);
	m_eState = eConnecting;

	return true;
}

bool CConnector::Connect(int family, const char *hostname, int port)
{
	if (m_eState != eConnecting)
	{
		return false;
	}

	m_pDns = evdns_base_new(m_pReactor->GetEventBase(), 0);
	int nResult = bufferevent_socket_connect_hostname(m_pBev, NULL, family, hostname, port);
	if (nResult != 0)
	{
		////监听出错
		evdns_base_free(m_pDns, 0);
		m_pDns = NULL;
		return false;
	}

	SetState(eConnected);
	return true;
}

void CConnector::ShutDown()
{
	if (m_eState != eUnConnected)
	{
		if (m_pDns)
		{
			evdns_base_free(m_pDns, 0);
			m_pDns = NULL;
		}

		CBufferEvent::ShutDown();
		m_eState = eUnConnected;
	}
}

void CConnector::OnEvent(short events)
{
	if (events & BEV_EVENT_CONNECTED)
	{
		SetState(eConnected);
		return;
	}

	CBufferEvent::OnEvent(events);
}

