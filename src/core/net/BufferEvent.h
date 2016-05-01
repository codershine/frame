class CReactor;

typedef unsigned int(*BUFFEREVENT_READ_CALLBACK)(unsigned int nId, void*data, size_t nSize);

class CBufferEvent :public IReactorHandle
{
public:
	CBufferEvent(unsigned int nId, CReactor* pReactor);
	virtual ~CBufferEvent();

	virtual void RegisteToReactor();
	virtual void UnRegisteToReactor();
	virtual void ShutDown();
	virtual void Write(const void* data, size_t size);
	virtual void OnRead();
	virtual void OnEvent(short events);
	virtual bool IsConnected() = 0;
	inline unsigned int GetId() const { return m_nId; };

	static void SetReadCallBack(BUFFEREVENT_READ_CALLBACK fReadCallBack);
private:
	static void _readcb(struct bufferevent *bev, void *user_data);
	static void _eventcb(struct bufferevent *bev, short events, void *user_data);
protected:
	unsigned int m_nId; //
	CReactor* m_pReactor;
	struct bufferevent *m_pBev;
public:
	static BUFFEREVENT_READ_CALLBACK s_fBufferEventReadCallBack;
};

