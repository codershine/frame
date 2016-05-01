#include "stdafx.h"

class CReadHandle :public CEasyReadHandle<CReadHandle>
{
protected:
	virtual unsigned int OnRead(unsigned int nId, void*data, size_t nSize){
		printf("%d %s\n", nId, string((char*)data, nSize).c_str());
		return 0;
	}
};


int main()
{
	CBufferEvent::SetReadCallBack(CEasyReadHandle<CReadHandle>::ReadHandle);
	CNet* pNet = CNet::getInstance();
	if (pNet->Listen("127.0.0.1", 9995))
	{
		while (true)
		{
			pNet->Dispatch();
			Sleep(2);
		}
	}


}
	