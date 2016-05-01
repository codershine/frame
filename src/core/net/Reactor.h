class IReactorHandle;

class CReactor
{
public:
	CReactor();
	~CReactor();

	static CReactor* CreateReactor();

	bool Init();

	inline struct event_base * GetEventBase(){ return m_pBase; }

	void RegisteReactorHandle(IReactorHandle*);
	void UnRegisteReactorHandle(IReactorHandle*);

	void Dispatch(int flag);
	void ShutDown();
private:
	struct event_base *m_pBase;
};