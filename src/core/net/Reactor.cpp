#include "stdafx.h"

CReactor::CReactor()
{

}

CReactor::~CReactor()
{
	ShutDown();
}

bool CReactor::Init()
{
	if (m_pBase)
	{
		return false;
	}

#ifdef WIN32
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
#endif

	m_pBase = event_base_new();
	if (!m_pBase) {
		return false;
	}

	return true;
}

CReactor* CReactor::CreateReactor()
{
	CReactor* pRet = new CReactor;
	if (pRet->Init())
	{
		return pRet;
	}

	return NULL;
}

void CReactor::RegisteReactorHandle(IReactorHandle* pHandle)
{
	pHandle->RegisteToReactor();
}

void CReactor::UnRegisteReactorHandle(IReactorHandle* pHandle)
{
	pHandle->UnRegisteToReactor();
}

void CReactor::Dispatch(int flag)
{
	event_base_loop(m_pBase, flag);
}

void CReactor::ShutDown()
{
	if (m_pBase)
	{
		event_base_free(m_pBase);
	}
	
	WSACleanup();
}



