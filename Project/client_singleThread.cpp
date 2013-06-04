#include"ld.h"

int main(int argc , char* argv [])
{
    ACE_INET_Addr srvr(50000, ACE_LOCALHOST);

    ACE_SOCK_Connector connector;
    ACE_SOCK_Stream peer;

    if(-1 == connector.connect(peer, srvr))
        ACE_ERROR_RETURN((LM_ERROR, LD_T("%p\nconnect")), 1);

    int bc;
    char buf[64];
    peer.send_n("uptime\n", 7);
    bc = peer.recv(buf, sizeof(buf));

    LD_DEBUG("retval: %d\nrecv info:%s", bc, buf);
    
    return 0;
}

