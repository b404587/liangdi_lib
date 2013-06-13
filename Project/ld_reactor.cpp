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


int ACE_TMAIN(int,ACE_TCHAR*[])
{
	ACE_INET_Addr addrListen("127.0.0.1:50001");
	LdEvtHandler ldHandler;
	ldHandler.reactor(ACE_Reactor::instance());
	if(ldHandler.open(addrListen) == -1)
		return 1;

	ACE_Reactor::instance()->run_reactor_event_loop();
	return 0;
}

