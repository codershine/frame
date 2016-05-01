#include "stdafx.h"

CNet::CNet() 
{
	m_pReactor = CReactor::CreateReactor();
	assert(m_pReactor);
}

CNet::~CNet()
{

}

bool CNet::Listen(const char* sAddr, unsigned short port)
{
	assert(sAddr);

	m_pListener = CListener::CreateListener(m_pReactor);
	return m_pListener->Listen(sAddr, port, this);
}

void CNet::Dispatch(int flag)
{
	m_pReactor->Dispatch(flag);
	ReleaseCloseBufferEvent(1000);
}

void CNet::Close()
{
	ReleaseAllBufferEvent();

	if (m_pListener)
	{
		delete m_pListener;
	}

	if (m_pReactor)
	{
		delete m_pReactor;
	}

	delete this;
}

void CNet::OnAccept(evutil_socket_t fd)
{
	unsigned int nId = GenId();
	CAcceptor* pAcceptor = CAcceptor::CreateAcceptor(nId, m_pReactor, fd);
	if (pAcceptor)
	{
		m_mId2BufferEvent[nId] = pAcceptor;
	}
}

unsigned int CNet::Connect(int family, const char *hostname, int port)
{
	unsigned int nId = GenId();
	CConnector* pConnector = CConnector::CreateConnector(nId, m_pReactor);
	if (pConnector && pConnector->Connect(family, hostname, port))
	{
		m_mId2BufferEvent[nId] = pConnector;
		return nId;
	}

	return 0;
}

void CNet::ShutDown(unsigned int nId)
{
	map<unsigned int, CBufferEvent*>::iterator itr = m_mId2BufferEvent.find(nId);
	if (itr != m_mId2BufferEvent.end())
	{
		CBufferEvent* pBufferEvent = itr->second;
		pBufferEvent->ShutDown();
	}
}

void CNet::SendData(unsigned int nId, void*data, size_t size)
{
	map<unsigned int, CBufferEvent*>::iterator itr = m_mId2BufferEvent.find(nId);
	if (itr != m_mId2BufferEvent.end())
	{
		CBufferEvent* pBufferEvent = itr->second;
		pBufferEvent->Write(data,size);
	}
}

void CNet::ReleaseCloseBufferEvent(int count)
{
	int nCount = 0;
	while (m_lBufferEvent.size() > 0 && nCount < count)
	{
		++nCount;
		list<CBufferEvent*>::iterator itr = m_lBufferEvent.begin();
		delete *itr;
		m_lBufferEvent.erase(itr);
	}
}

void CNet::ReleaseAllBufferEvent()
{
	for (map<unsigned int, CBufferEvent*>::iterator itr = m_mId2BufferEvent.begin(); itr != m_mId2BufferEvent.end(); ++itr)
	{
		delete itr->second;
	}

	m_mId2BufferEvent.clear();

	ReleaseCloseBufferEvent(m_lBufferEvent.size());
}

unsigned int CNet::GenId()
{
	static unsigned int nId = 0;
	++nId;
	if (nId == 0) //0作为特殊用途保留
	{
		nId = 1;
	}
	return nId;
}

CBufferEvent* CNet::GetBufferEventById(unsigned int nId)
{
	map<unsigned int, CBufferEvent*>::iterator itr = m_mId2BufferEvent.find(nId);
	if (itr != m_mId2BufferEvent.end())
	{
		return itr->second;
	}

	return NULL;
}









