#include <string>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <new>
#include <memory>
#include <assert.h>

#include <list>
#include <map>

using namespace std;

#ifdef WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
# ifdef _XOPEN_SOURCE_EXTENDED
#  include <arpa/inet.h>
# endif
#include <sys/socket.h>
#endif


#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <event2/dns.h>

#include "export.h"
#include "core/patten/Singleton.h"

#include "core/net/ReactorHandle.h"
#include "core/net/ConnectorHandle.h"
#include "core/net/ListenerHandle.h"
#include "core/net/BufferEvent.h"
#include "core/net/Acceptor.h"
#include "core/net/Listener.h"
#include "core/net/Connector.h"
#include "core/net/Reactor.h"
#include "core/net/Net.h"
#include "core/net/EasyReadHandle.h"
