#include"ld.h"

#ifdef _MSC_VER 
#pragma comment(lib, "ACE.lib")
#endif

int main(int,char*[])
{

    ACE_INET_Addr port_to_listen ("127.0.0.1:50001");
	
    ACE_SOCK_Acceptor acceptor;

    if (acceptor.open (port_to_listen, 1) == -1)
      ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("acceptor.open error:%p\n"), ACE_TEXT("127.0.0.1:50001")),100);

    while (1)
    {
        ACE_SOCK_Stream peer;
        ACE_INET_Addr peer_addr;
        ACE_Time_Value timeout (10, 0);

        if (acceptor.accept (peer, &peer_addr, &timeout, 0) == -1)
        {
            if (ACE_OS::last_error() == EINTR)
                ACE_DEBUG((LM_DEBUG, LD_T("(%P|%t) Interrupted while waiting for connection\n") ));
             else if (ACE_OS::last_error() == ETIMEDOUT)
                ACE_DEBUG ((LM_DEBUG, LD_T("(%P|%t) Timeout while waiting for connection\n")));
        }
        else
        {
            ACE_TCHAR peer_name[MAXHOSTNAMELEN];
            peer_addr.addr_to_string (peer_name, MAXHOSTNAMELEN);
            LD_DEBUG(LD_T("(%P|%t) Connection from %s\n"),peer_name);
            // Listing 5
            // Listing 7 code/ch06
            char buffer[4096];
            ssize_t bytes_received;

            while ((bytes_received = peer.recv (buffer, sizeof(buffer))) != -1)
            {
              peer.send_n (buffer, bytes_received);
            }

          peer.close ();
          // Listing 7
        }

    }
    return 0;
}

