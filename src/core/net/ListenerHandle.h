class IListenerHandle
{
public:
	virtual void OnAccept(evutil_socket_t fd){};
};