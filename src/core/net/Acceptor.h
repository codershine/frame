class CReactor;

class CAcceptor :public CBufferEvent
{
public:
	enum CAcceptor_State
	{
		eConnected,
		eUnConnected
	};


public:
	CAcceptor(unsigned int nId, CReactor* pReactor);

	static CAcceptor* CreateAcceptor(unsigned int nId, CReactor* pReactor, evutil_socket_t fd);

	bool Init(evutil_socket_t fd);

	virtual void ShutDown();
	bool IsConnected(){ return m_eState == eConnected; }
private:
	CAcceptor_State m_eState;
};