class CReactor;
class IReactorHandle;
class IListenerHandle;

class CListener
{
public:
	enum CListener_State
	{
		eUnListen,
		eListened
	};

public:
	CListener(CReactor* pReactor);
	~CListener();

	static CListener* CreateListener(CReactor* pReactor);
	static void _listencb(struct evconnlistener *listener, evutil_socket_t fd,
							struct sockaddr *sa, int socklen, void *user_data);

	bool Listen(const char* sAddr, unsigned short port, IListenerHandle* pListenerHandle);
	inline CListener_State GetState() const{ return m_eState; }
	inline void SetState(CListener_State eState){ m_eState = eState; };
	void ShutDown();

	void OnAccept(evutil_socket_t fd);

private:
	CReactor* m_pReactor;
	CListener_State m_eState;
	IListenerHandle* m_pListenerHandle;
	struct evconnlistener *m_pListener;
};