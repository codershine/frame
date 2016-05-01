class CReactor;

class CConnector :public CBufferEvent
{
public:
	enum CConnector_State
	{
		eConnected,
		eConnecting,
		eUnConnected
	};
public:
	CConnector(unsigned int nId, CReactor* pReactor);

	static CConnector* CreateConnector(unsigned int nId, CReactor* pReactor);

	bool Connect(int family, const char *hostname, int port);

	bool Init();

	virtual bool IsConnected(){ return m_eState == eConnected; }
	virtual void ShutDown();
	virtual void OnEvent(short events);
	inline void SetState(CConnector_State eState){ m_eState = eState; }
	inline CConnector_State GetState(){ return m_eState; }
private:
	struct evdns_base * m_pDns;
	CConnector_State m_eState;

};