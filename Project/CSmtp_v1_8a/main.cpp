#include "CSmtp.h"
#include <iostream>
//#pragma comment(lib,"ACEd.lib")

int ACE_TMAIN (int, ACE_TCHAR *[])
//int main(int*, ACE_TCHAR*[])
{
	bool bError = false;

	try
	{
		CSmtp mail;

		mail.SetSMTPServer("smtp.163.com",25);
		mail.SetLogin("b404587");
		mail.SetPassword("...");
  		mail.SetSenderName("b40");
  		mail.SetSenderMail("b404587@163.com");
  		//mail.SetReplyTo("404579707@qq.com");
  		mail.SetSubject("The message");
  		mail.AddRecipient("404579707@qq.com");
  		mail.SetXPriority(XPRIORITY_NORMAL);
  		mail.SetXMailer("The Bat! (v3.02) Professional");
  		mail.AddMsgLine("Hello,");
		mail.AddMsgLine("");
		mail.AddMsgLine("...");
		mail.AddMsgLine("How are you today?");
		mail.AddMsgLine("");
		mail.AddMsgLine("Regards");
		mail.ModMsgLine(5,"regards");
		mail.DelMsgLine(2);
		mail.AddMsgLine("User");
		
  		mail.AddAttachment("01.txt");
  		//mail.AddAttachment("c:\\test2.exe");
		//mail.AddAttachment("c:\\test3.txt");
		mail.Send();
	}
	catch(ECSmtp e)
	{
		std::cout << "Error: " << e.GetErrorText().c_str() << ".\n";
		bError = true;
	}
	if(!bError)
		std::cout << "Mail was send successfully.\n";

	getchar();
	return 0;
}
