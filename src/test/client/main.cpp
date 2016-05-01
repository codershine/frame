#include "stdafx.h"

void main()
{
	CNet* pNet = CNet::getInstance();
	unsigned int nId = pNet->Connect(AF_INET, "127.0.0.1", 9995);
	CBufferEvent* pBufferEvent = pNet->GetBufferEventById(nId);

	while (1)
	{
		Sleep(1000);
		if (pBufferEvent->IsConnected())
		{
			EasySendData(nId, "1111", 4);
		}

		pNet->Dispatch(EVLOOP_NONBLOCK);
	}

}