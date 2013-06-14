#include"ld.h"

#ifdef _MSC_VER 
#ifdef NDEBUG
#pragma comment(lib, "ACE.lib")
#else
#pragma comment(lib, "ACEd.lib")
#endif
#endif


int main(int argc , char* argv [])
{
    ACE_INET_Addr srvr("127.0.0.1:50001");

    ACE_SOCK_Connector connector;
    ACE_SOCK_Stream peer;

    if(-1 == connector.connect(peer, srvr))
        ACE_ERROR_RETURN((LM_ERROR, LD_T("connect error: %p\n"), ACE_TEXT("127.0.0.1:50001")), 1);

    int bc;
    char buf[64] = {0};
    peer.send_n("uptime\n", 7);
    bc = peer.recv(buf, sizeof(buf));

    LD_DEBUG("retval: %d\nrecv info:%s", bc, buf);
    
    return 0;
}

