#include "ld.h"

#ifdef _MSC_VER 
#ifdef NDEBUG
#pragma comment(lib, "ACE.lib")
#else
#pragma comment(lib, "ACEd.lib")
#endif
#endif

class LdEvtHandler:public ACE_Event_Handler
{
public:
	virtual ~LdEvtHandler();
	int open(const ACE_INET_Addr& addr);

	virtual ACE_HANDLE get_handle()const
	{
		return acceptor_.get_handle();
	}

	virtual int handle_timeout (const ACE_Time_Value &current_time, const void *act = 0)
	{
		int * iArg = (int*)act;
		ACE_DEBUG((LM_DEBUG, ACE_TEXT("%D arg:%d\n"), *iArg));
		return 0;
	}

	virtual int handle_input(ACE_HANDLE fd=ACE_INVALID_HANDLE);

	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);
protected:
	ACE_SOCK_Acceptor acceptor_;
};

class LdService:public ACE_Event_Handler
{
public:
	ACE_SOCK_Stream& peer()
	{
		return sock_;
	}
	int open();
	virtual ACE_HANDLE get_handle()const
	{
		return sock_.get_handle();
	}
	
	virtual int handle_input(ACE_HANDLE fd=ACE_INVALID_HANDLE);
	virtual int handle_output(ACE_HANDLE fd=ACE_INVALID_HANDLE);
	virtual int handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask);

protected:
	ACE_SOCK_Stream sock_;
	ACE_Message_Queue<ACE_NULL_SYNCH> outputQueue_;
};

int LdEvtHandler::open(const ACE_INET_Addr& addr)
{
	if(acceptor_.open(addr, 1) == -1)
		ACE_ERROR_RETURN((LM_ERROR, ACE_TEXT("%p\n"), ACE_TEXT("acceptor.open")), -1);

	return reactor()->register_handler(this, ACCEPT_MASK);
}

int LdEvtHandler::handle_input(ACE_HANDLE fd)
{
	LdService* pClient;
	ACE_NEW_RETURN(pClient, LdService, -1);

	if(acceptor_.accept(pClient->peer()) == -1)
		ACE_ERROR_RETURN((LM_ERROR, ACE_TEXT("(%P|%t) %p\n"), 
						ACE_TEXT("Failed ot accept client connection")), -1);
	pClient->reactor(this->reactor());

	if(pClient->open() == -1)
		pClient->handle_close(ACE_INVALID_HANDLE, 0);

	return 0;
}
int LdEvtHandler::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
	if(acceptor_.get_handle() != ACE_INVALID_HANDLE)
	{
		ACE_Reactor_Mask m = ACCEPT_MASK|DONT_CALL;
		reactor()->remove_handler(this, m);
		acceptor_.close();
	}
	return 0;
}

LdEvtHandler::~LdEvtHandler()
{
	handle_close(ACE_INVALID_HANDLE, 0);
}


int LdService::open()
{
	ACE_TCHAR peerName[MAXHOSTNAMELEN];
	ACE_INET_Addr peerAddr;
	if(sock_.get_remote_addr(peerAddr) == 0 && 
		peerAddr.addr_to_string(peerName, MAXHOSTNAMELEN) ==0)
	{
		ACE_DEBUG((LM_DEBUG, ACE_TEXT("(%P|%t) connection from %s\n"), peerName));
	}

	return reactor()->register_handler(this, READ_MASK);
}

int LdService::handle_input(ACE_HANDLE fd)
{
	const size_t INPUT_SIZE = 4096;
	char buffer[INPUT_SIZE];
	ssize_t recv_cnt, send_cnt;

	if((recv_cnt = sock_.recv(buffer, sizeof(buffer))) <= 0)
	{
		ACE_DEBUG((LM_ERROR, ACE_TEXT("(%P|%t) Connection closed\n")));
		return -1;
	}

	send_cnt = sock_.send(buffer, recv_cnt);
	if(send_cnt == recv_cnt)
		return 0;
	if(send_cnt == -1 && ACE_OS::last_error() != EWOULDBLOCK)
		ACE_ERROR_RETURN((LM_ERROR, ACE_TEXT("(%P|%t) %p\n"), ACE_TEXT("send")), 0);

	if(send_cnt == -1)
		send_cnt = 0;

	ACE_Message_Block *mb;
	size_t remaining = size_t(recv_cnt - send_cnt);
	ACE_NEW_RETURN(mb, ACE_Message_Block(&buffer[send_cnt], remaining), -1);

	int outputOff = outputQueue_.is_empty();
	ACE_Time_Value nowait(ACE_OS::gettimeofday());
	if(outputQueue_.enqueue_tail(mb, &nowait) == -1)
	{
		ACE_DEBUG((LM_ERROR, ACE_TEXT("(%P|%t) %p; dixcarding data"),
					ACE_TEXT("enqueue failed")));
		mb->release();
		return 0;
	}

	if(outputOff)
		return reactor()->register_handler(this, WRITE_MASK);
	return 0;
}

int LdService::handle_output(ACE_HANDLE fd)
{
	ACE_Message_Block* mb;
	ACE_Time_Value nowait(ACE_OS::gettimeofday());
	while(0 == outputQueue_.dequeue_head(mb, &nowait))
	{
		ssize_t send_cnt = sock_.send(mb->rd_ptr(), mb->length());
		if(send_cnt == -1)
			ACE_DEBUG((LM_ERROR, ACE_TEXT("(%P|%t %p\n)"), ACE_TEXT("send")));
		else
			mb->rd_ptr((size_t)send_cnt);
		if(mb->length() > 0)
		{
			outputQueue_.enqueue_head(mb);
			break;
		}
		mb->release();
	}
	return outputQueue_.is_empty() ? -1: 0;
}

int LdService::handle_close(ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
{
	if(close_mask == WRITE_MASK)
		return 0;
	close_mask = ALL_EVENTS_MASK | DONT_CALL;
	reactor()->remove_handler(this, close_mask);
	sock_.close();
	outputQueue_.flush();
	delete this;
	return 0;
}

class ClientService :
  public ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH>
{
	typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> super;

public:
	int open (void * p = 0)
	{
		if (super::open (p) == -1)
		  return -1;
		
		ACE_TCHAR peer_name[MAXHOSTNAMELEN];
		ACE_INET_Addr peer_addr;
		if (this->peer ().get_remote_addr (peer_addr) == 0 &&
			peer_addr.addr_to_string (peer_name, MAXHOSTNAMELEN) == 0)
		  ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) Connection from %s\n"),
					  peer_name));
		return 0;

	}

	// Called when input is available from the client.
	virtual int handle_input (ACE_HANDLE fd = ACE_INVALID_HANDLE)
	{
		const size_t INPUT_SIZE = 4096;
		char buffer[INPUT_SIZE];
		ssize_t recv_cnt, send_cnt;
		
		recv_cnt = this->peer ().recv (buffer, sizeof(buffer));
		if (recv_cnt <= 0)
		  {
			ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%P|%t) Connection closed\n")));
			return -1;
		  }
		
		send_cnt = this->peer ().send (buffer, static_cast<size_t> (recv_cnt));
		if (send_cnt == recv_cnt)
		  return 0;
		if (send_cnt == -1 && ACE_OS::last_error () != EWOULDBLOCK)
		  ACE_ERROR_RETURN ((LM_ERROR,ACE_TEXT ("(%P|%t) %p\n"),
							 ACE_TEXT ("send")),
							0);
		if (send_cnt == -1)
		  send_cnt = 0;
		ACE_Message_Block *mb = 0;
		size_t remaining =
		  static_cast<size_t> ((recv_cnt - send_cnt));
		ACE_NEW_RETURN (mb, ACE_Message_Block (remaining), -1);
		mb->copy (&buffer[send_cnt], remaining);
		int output_off = this->msg_queue ()->is_empty ();
		ACE_Time_Value nowait (ACE_OS::gettimeofday ());
		if (this->putq (mb, &nowait) == -1)
		  {
			ACE_ERROR ((LM_ERROR,
						ACE_TEXT ("(%P|%t) %p; discarding data\n"),
						ACE_TEXT ("enqueue failed")));
			mb->release ();
			return 0;
		  }
		if (output_off)
		  return this->reactor ()->register_handler
			(this, ACE_Event_Handler::WRITE_MASK);
		return 0;

	}

	// Called when output is possible.
	virtual int handle_output (ACE_HANDLE fd = ACE_INVALID_HANDLE)
	{
		ACE_Message_Block *mb = 0;
		ACE_Time_Value nowait (ACE_OS::gettimeofday ());
		while (-1 != this->getq (mb, &nowait))
		  {
			ssize_t send_cnt =
			  this->peer ().send (mb->rd_ptr (), mb->length ());
			if (send_cnt == -1)
			  ACE_ERROR ((LM_ERROR,
						  ACE_TEXT ("(%P|%t) %p\n"),
						  ACE_TEXT ("send")));
			else
			  mb->rd_ptr (static_cast<size_t> (send_cnt));
			if (mb->length () > 0)
			  {
				this->ungetq (mb);
				break;
			  }
			mb->release ();
		  }
		return (this->msg_queue ()->is_empty ()) ? -1 : 0;

	}

	// Called when this handler is removed from the ACE_Reactor.
	virtual int handle_close (ACE_HANDLE handle, ACE_Reactor_Mask close_mask)
	{
		if (close_mask == ACE_Event_Handler::WRITE_MASK)
			return 0;
		return super::handle_close (handle, close_mask);
	}
};


typedef ACE_Acceptor<ClientService, ACE_SOCK_ACCEPTOR> ClientAcceptor;


int ACE_TMAIN(int,ACE_TCHAR*[])
{
	ACE_INET_Addr port_to_listen ("127.0.0.1:50001");
	ClientAcceptor acceptor;
	 if (acceptor.open (port_to_listen, ACE_Reactor::instance (), ACE_NONBLOCK) == -1)
	 	return 1;

#if 0
	ACE_INET_Addr addrListen("127.0.0.1:50001");
	LdEvtHandler ldHandler;
	ldHandler.reactor(ACE_Reactor::instance());
	if(ldHandler.open(addrListen) == -1)
		return 1;

	ACE_Time_Value initDelay(3);
	ACE_Time_Value interval(5);
	int *iArg = new int(5);
	ACE_Reactor::instance()->schedule_timer(&ldHandler, iArg, initDelay, interval);
#endif
	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}

