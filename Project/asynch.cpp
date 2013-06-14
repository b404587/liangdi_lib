#include "ld.h"

#ifdef _MSC_VER 
#ifdef NDEBUG
#pragma comment(lib, "ACE.lib")
#else
#pragma comment(lib, "ACEd.lib")
#endif
#endif

class HA_Proactive_Service : public ACE_Service_Handler
{
public:
  ~HA_Proactive_Service ()
   {
     if (this->handle () != ACE_INVALID_HANDLE)
       ACE_OS::closesocket (this->handle ());
   }

  virtual void open (ACE_HANDLE h, ACE_Message_Block& )
  {
	  this->handle (h);
	  if (this->reader_.open (*this) != 0 ||
		  this->writer_.open (*this) != 0	)
		{
		  ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"),
					  ACE_TEXT ("HA_Proactive_Service open")));
		  delete this;
		  return;
		}
	  
	  ACE_Message_Block *mb = 0;
	  ACE_NEW_NORETURN (mb, ACE_Message_Block (1024));
	  if (this->reader_.read (*mb, mb->space ()) != 0)
		{
		  ACE_ERROR ((LM_ERROR, ACE_TEXT ("%p\n"),
					  ACE_TEXT ("HA_Proactive_Service begin read")));
		  mb->release ();
		  delete this;
		  return;
		}
	  
	  // mb is now controlled by Proactor framework.
	  return;

  }

  // This method will be called when an asynchronous read
  // completes on a stream.
  virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result)
  {
	  ACE_Message_Block &mb = result.message_block ();
	  if (!result.success () || result.bytes_transferred () == 0)
		{
		  mb.release ();
		  delete this;
		}
	  else
		{
		  if (this->writer_.write (mb, mb.length ()) != 0)
			{
			  ACE_ERROR ((LM_ERROR,
						  ACE_TEXT ("%p\n"),
						  ACE_TEXT ("starting write")));
			  mb.release ();
			}
		  else
			{
			  ACE_Message_Block *new_mb;
			  ACE_NEW_NORETURN (new_mb, ACE_Message_Block (1024));
			  this->reader_.read (*new_mb, new_mb->space ());
			}
		}
	  return;

  }

  // This method will be called when an asynchronous write
  // completes on a stream.
  virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result)
  {
	  result.message_block ().release ();
	  return;
  }

private:
  ACE_Asynch_Read_Stream reader_;
  ACE_Asynch_Write_Stream writer_;
};

class HA_Proactive_Acceptor :
    public ACE_Asynch_Acceptor<HA_Proactive_Service>
{
public:
  virtual int validate_connection(const ACE_Asynch_Accept::Result& result,
     				const ACE_INET_Addr &remote,const ACE_INET_Addr &local)
  {
	return 0;
  }
};


int ACE_TMAIN (int, ACE_TCHAR *[])
{
  // Listing 5 code/ch08
 // #if 0
  ACE_INET_Addr listen_addr("127.0.0.1:50001");     // Set up with listen port
  HA_Proactive_Acceptor aio_acceptor;
  if (0 != aio_acceptor.open (listen_addr,
                              0,     // bytes_to_read
                              0,     // pass_addresses
                              ACE_DEFAULT_ASYNCH_BACKLOG,
                              1,     // reuse_addr
                              0,     // proactor
                              1))    // validate_new_connection
    ACE_ERROR_RETURN ((LM_ERROR, ACE_TEXT ("%p\n"),
                       ACE_TEXT ("acceptor open")), 1);
  // Listing 5
//#endif
#if 0
  // Listing 6 code/ch08
  ACE_INET_Addr peer_addr("127.0.0.1:50001");    // Set up peer addr
  ACE_Asynch_Connector<HA_Proactive_Service> aio_connect;
  aio_connect.connect (peer_addr);
  // Listing 6
#endif

  // Listing 7 code/ch08
  ACE_Proactor::instance ()->proactor_run_event_loop ();
  // Listing 7
  return 0;
}


