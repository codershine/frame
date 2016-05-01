#define  EASY_HEADER_FLAG 0xAB0528CD

typedef struct StructEasyReadHeader 
{
	unsigned int nFlag;
	unsigned int nLength;
}StructEasyReadHeader;

template <class T>
class CEasyReadHandle :public TSingleton<T>
{
public:
	CEasyReadHandle() :m_nToRead(sizeof(StructEasyReadHeader)), m_bReadHeader(true){};
	~CEasyReadHandle(){};
	
	static unsigned int ReadHandle(unsigned int nId, void*data, size_t nSize);

protected:
	unsigned int OnEasyRead(unsigned int nId, void*data, size_t nSize);
	virtual unsigned int OnRead(unsigned int nId, void*data, size_t nSize){ return 0; };
private:
	unsigned int m_nToRead;
	bool m_bReadHeader;
};

template <class T>
unsigned int CEasyReadHandle<T>::OnEasyRead(unsigned int nId, void*data, size_t nSize)
{
	if (!data)
	{
		return m_nToRead;
	}

	if (m_bReadHeader)
	{
		StructEasyReadHeader header = *(StructEasyReadHeader*)data;
		if (header.nFlag != EASY_HEADER_FLAG) //头不对就关闭客户端吧
		{
			CNet::getInstance()->ShutDown(nId);
			return 0;
		}

		m_bReadHeader = false;
		m_nToRead = header.nLength;
		return m_nToRead;
	}

	m_nToRead = OnRead(nId, data, nSize);
	if (m_nToRead == 0)
	{
		m_bReadHeader = true;
		m_nToRead = sizeof(StructEasyReadHeader); //接着继续读
	}
	return m_nToRead;
}

template <class T>
unsigned int CEasyReadHandle<T>::ReadHandle(unsigned int nId, void*data, size_t nSize)
{
	T* pClass = T::getInstance();
	return pClass->OnEasyRead(nId, data, nSize);
}


extern void EasySendData(unsigned int nId, void*data, size_t size);
	