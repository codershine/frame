#include "stdafx.h"

#define CBufferEvent_STACK_READ_LENGTH 65536

BUFFEREVENT_READ_CALLBACK CBufferEvent::s_fBufferEventReadCallBack = NULL;

CBufferEvent::CBufferEvent(unsigned int nId, CReactor* pReactor) :m_nId(nId), m_pReactor(pReactor), m_pBev(NULL)
{

}


CBufferEvent::~CBufferEvent()
{

}

void CBufferEvent::RegisteToReactor()
{
	bufferevent_setcb(m_pBev, _readcb, NULL, _eventcb, this);
	bufferevent_enable(m_pBev, EV_WRITE);
	bufferevent_enable(m_pBev, EV_READ);
}

void CBufferEvent::UnRegisteToReactor()
{
	bufferevent_setcb(m_pBev, NULL, NULL, NULL, NULL);
}

void CBufferEvent::ShutDown()
{
	m_pReactor->UnRegisteReactorHandle(this);
	bufferevent_free(m_pBev);
	m_pBev = NULL;
}

void CBufferEvent::Write(const void* data, size_t size)
{
	if (!IsConnected())
	{
		return;
	}
	//����libevent��ˬ�ĵط�
	bufferevent_write(m_pBev, data, size);
}

void CBufferEvent::OnEvent(short events)
{
	if (events & BEV_EVENT_EOF || events & BEV_EVENT_ERROR) {
		ShutDown();
	}
}

void CBufferEvent::OnRead()
{
	if (!s_fBufferEventReadCallBack)
	{
		return;
	}

	if (!IsConnected())
	{
		return;
	}

	unsigned int nToRead = 0;

	struct evbuffer *input = bufferevent_get_input(m_pBev);
	size_t nTotalLen = evbuffer_get_length(input);

	nToRead = s_fBufferEventReadCallBack(GetId(), NULL, 0); //��ȡ�߼�����Ҫ��ȡ���ֽ���

	while (1)
	{
		if (!IsConnected()) //�ص����̹ر��������ߵ�
		{
			break;
		}

		if (nTotalLen < nToRead)//��ʱ����
		{
			break;
		}

		if (nToRead == 0)//�߼��㲻���������ȡ��
		{
			break;
		}
		size_t nRead;

		if (nToRead <= CBufferEvent_STACK_READ_LENGTH)
		{
			char data[CBufferEvent_STACK_READ_LENGTH];
			nRead = bufferevent_read(m_pBev, data, nToRead);
			if (nRead == 0 || nRead != nToRead) //�д���ֱ�ӹر�
			{
				ShutDown();
				break;
			}

			nTotalLen = nTotalLen - nRead;
			nToRead = s_fBufferEventReadCallBack(GetId(), data, nRead);
		}
		else
		{
			shared_ptr<char> data(new char[nToRead], std::default_delete<char[]>());
			nRead = bufferevent_read(m_pBev, data.get(), nToRead);
			if (nRead == 0 || nRead != nToRead) //�д���ֱ�ӹر�
			{
				ShutDown();
				break;
			}

			nTotalLen = nTotalLen - nRead;
			nToRead = s_fBufferEventReadCallBack(GetId(), data.get(), nRead);
		}

	}

}

void CBufferEvent::_readcb(struct bufferevent *bev, void *user_data)
{
	CBufferEvent* pThis = (CBufferEvent*)user_data;
	pThis->OnRead();
}


void CBufferEvent::_eventcb(struct bufferevent *bev, short events, void *user_data)
{
	CBufferEvent* pThis = (CBufferEvent*)user_data;
	pThis->OnEvent(events);
}

void CBufferEvent::SetReadCallBack(BUFFEREVENT_READ_CALLBACK fReadCallBack)
{
	s_fBufferEventReadCallBack = fReadCallBack;
}