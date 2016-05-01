class CBufferEvent;
class CAcceptor;
class CReactor;
class CListener;
class CConnector;
class IConnectorHandle;
class IListenerHandle;

class CNet :public TSingleton<CNet>, IListenerHandle
{
public:
	bool Listen(const char* sAddr, unsigned short port);
	void Dispatch(int flag = 0);
	void ReleaseAllBufferEvent();
	void ReleaseCloseBufferEvent(int count);
	void Close();
	void OnAccept(evutil_socket_t fd);
	unsigned int Connect(int family, const char *hostname, int port);
	void ShutDown(unsigned int nId);
	void SendData(unsigned int nId, void*data, size_t size);
	unsigned int GenId();
	CBufferEvent* GetBufferEventById(unsigned int nId);
private:
	CNet();
	~CNet();
	friend class TSingleton<CNet>;

private:
	CReactor* m_pReactor;
	CListener* m_pListener;
	map<unsigned int, CBufferEvent*> m_mId2BufferEvent;
	list<CBufferEvent*> m_lBufferEvent; //待关闭的连接
};


