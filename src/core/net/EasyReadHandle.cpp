#include "stdafx.h"

void EasySendData(unsigned int nId, void*data, size_t size){
	StructEasyReadHeader header;
	header.nFlag = EASY_HEADER_FLAG;
	header.nLength = size;

	CNet::getInstance()->SendData(nId, (void*)&header, sizeof(StructEasyReadHeader));
	CNet::getInstance()->SendData(nId, (void*)data, size);
}
