#include"ld.h"

#ifdef _MSC_VER 
#ifdef NDEBUG
#pragma comment(lib, "ACE.lib")
#else
#pragma comment(lib, "ACEd.lib")
#endif
#endif

class DeviceRepository
{
public:
	void updateDevice(int deviceId)
	{
		ACE_GUARD(ACE_Thread_Mutex, mon, mutex_);
		//ACE_Guard<ACE_Thread_Mutex> guard(mutex_);
		//mutex_.acquire();
		ACE_DEBUG((LM_DEBUG, ACE_TEXT("%t Updating device %d\n"), deviceId));
		ACE_OS::sleep(1);
		//mutex_.release();
	}
private:
	ACE_Thread_Mutex mutex_;
};

class Device_Repository
{
public:
	Device_Repository():owner_(0){}

	int is_free()
	{
		return owner_ ==0;
	}

	int is_owner(ACE_Task_Base* tb)
	{
		return (owner_ == tb);
	}
	ACE_Task_Base* get_owner()
	{
		return owner_;
	}
	void set_owner(ACE_Task_Base* tb)
	{
		owner_ = tb;
	}
	int update_device(int device_id)
	{
		ACE_DEBUG ((LM_DEBUG, ACE_TEXT ("(%t) %T Updating device %d\n"),
					device_id));
		
		ACE_OS::sleep (1);
		return 0;
	}
private:
	ACE_Task_Base* owner_;
};

class CmdHandler:public ACE_Task_Base
{
public:
	CmdHandler(Device_Repository& rep,
					ACE_Condition<ACE_Thread_Mutex>& wait,
					ACE_Thread_Mutex& mutex):rep_(rep),waitCond_(wait), mutex_(mutex)
	{
	}
	
	virtual int svc()
	{
		for(int i=0;i<10;++i)
		{
			ACE_DEBUG((LM_DEBUG, ACE_TEXT("%t i:%d1\n"), i));
			mutex_.acquire();

			while(!rep_.is_free())
			{
				waitCond_.wait();
			}
				
			rep_.set_owner(this);
			mutex_.release();

			rep_.update_device(i);

			rep_.set_owner(0);

			waitCond_.signal();
			ACE_OS::sleep (1);
		}
		return 0;
	}

private:
	Device_Repository& rep_;
	ACE_Condition<ACE_Thread_Mutex>& waitCond_;
	ACE_Thread_Mutex& mutex_;
};

int ACE_TMAIN(int,ACE_TCHAR*[])
{
	ACE_DEBUG((LM_DEBUG, ACE_TEXT("%t Main Thread running\n")));
	Device_Repository rep;
	ACE_Thread_Mutex rep_mutex;
	ACE_Condition<ACE_Thread_Mutex> wait(rep_mutex);
	CmdHandler h1(rep, wait, rep_mutex);
	CmdHandler h2(rep, wait, rep_mutex);
	h1.activate();
	h2.activate();

	h1.wait();
	h2.wait();

	getchar();
	return 0;
}
