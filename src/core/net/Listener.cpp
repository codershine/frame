#include "stdafx.h"

CListener::CListener(CReactor* pReactor) : m_pReactor(pReactor), m_eState(eUnListen), 
											m_pListener(NULL),m_pListenerHandle(NULL)
{

}

CListener* CListener::CreateListener(CReactor* pReactor)
{
	return new CListener(pReactor);
}

bool CListener::Listen(const char* sAddr, unsigned short port, IListenerHandle* pListenerHandle)
{
	assert(sAddr);

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(0x7f000001L);
	//sin.sin_addr = inet_addr(sAddr);
	sin.sin_port = htons(port);

	m_pListener = evconnlistener_new_bind(m_pReactor->GetEventBase(), _listencb, (void *)this,
		LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 1000,
		(struct sockaddr*)&sin,
		sizeof(sin));

	if (m_pListener)
	{
		m_pListenerHandle = pListenerHandle;
		m_eState = eListened;
		return true;
	}

	return false;
}

void CListener::_listencb(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sa, int socklen, void *user_data)
{
	printf("on accept\n");
	CListener* pThis = (CListener*)user_data;
	pThis->SetState(eListened);
	pThis->OnAccept(fd);
}

void CListener::ShutDown()
{
	if (m_eState == eListened)
	{
		if (m_pListener)
		{
			evconnlistener_free(m_pListener);
			m_pListener = NULL;
		}

		m_eState = eUnListen;
	}
}

void CListener::OnAccept(evutil_socket_t fd)
{
	if (m_pListenerHandle)
	{
		m_pListenerHandle->OnAccept(fd);
	}
}

CListener::~CListener()
{
	ShutDown();
}

