#ifndef LD_LOG_H_
#define LD_LOG_H_

/*log level Macro: 
ACE_DEBUG
ACE_ERROR
ACE_TRACE
*/

/*severity level:
LM_TRACE
LM_DEBUG
LM_INFO
LM_NOTICE
LM_WARNING
LM_ERROR
LM_CRITICAL
LM_ALERT
LM_EMERGENCY
*/

/*
���������Ԥ��������ACE_NDEBUG,
ACE_DEBUG��չ��Ϊһ������
*/

/*
ACE��־��ʽ��ָ��
��ʽ����        ��������        ��ʾ
A:                              ACE_timer_t            ������
a:                              -                            ����ʾ�������ֹ����
c:                              char                        �����ַ�
C:                              char*                       �ַ���(խ�ַ�)
i,d:                            int                         ʮ������
I:                              -                           ����ACE_Trace::get_nesting_indent()��õ�Ƕ������������
e,E,f,F,g,G:                double                  ˫���ȸ�����
l:                              -                           ��־�����֮�����к�
M:                           -                              ��Ϣ���ؼ�����ı���ʽ
m:                          -                               ��errnoֵ��Ӧ����Ϣ����strerror()����������һ��
N:                           -                              ��־�������ļ�������
n:                           -                              ����ACE_Log_Msg::open()�ĳ�����
o:                          int                             �˽�����
P:                           -                              ��ǰ���̵�ID
p:                           ACE_TCHAR*             ָ�����ַ������������ʵ���error��Ϣ����perror����������һ��
Q:                           ACE_UINT64            ʮ������
r:                          void(*)()                   ����ʾ������ָ���ĺ���
R:                           int                            ʮ������
S:                           int                            ��д�õ��źŵ�����
s:                          ACE_TCHAR*              �ַ�����ȡ����ACE_TCHAR���ͣ�խ�Ļ��߿��
T:                          -                                   ��ǰʱ�䣬��ʽ��hour:minute:sec.usec
D:                            -                                 ʱ�������ʽ��month/day/year/ hour:minute:sec.usec
t:                           -                                  �����̵߳�(calling thread)ID(����ǵ��߳̾���1)
u:                            int                               �޷���ʮ������
w:                            wchar_t                   �������ַ�
W:                         wchar_t*                     ���ַ���
x,X:                        int                             ʮ��������
@:                           void*                      ��ʮ�����Ʊ�ʾ��ָ��ֵ
%:                           N/A                            �����ٷֺ�:"%"
*/

/*
ACE��־��
ACE_ASSERT(test)
ACE_HEX_DUMP((level, buffer, size[,text]))
ACE_RETURN(value)
ACE_ERROR_RETURN((level, string, ...), value)
ACE_ERROR((level, string, ...))
ACE_DEBUG((level, string, ...))
ACE_ERROR_INIT(value, flag)
ACE_ERROR_BREAK((level, string, ...))
ACE_TRACE(string)
*/

/*
��־���Ƿ�����������ã�ȡ���ڱ����ѡ��:
ACE_NTRACE
ACE_NDEBUG
ACE_NLOGGING
���磬define ACE_NTRACE 1 ������־��#define ACE_NTRACE 0 ����
ע�⣬ACE_TRACE ȡ����ACE_NTRACE ��ACE_NDEBUG��������
*/

#include <ace/Log_Msg.h>

<<<<<<< HEAD
#define ACE_DEBUG_PREFIX                ACE_TEXT("\nld_Debug %D ")
#define ACE_INFO_PREFIX                 ACE_TEXT("\nld_Info %D ")
#define ACE_NOTICE_PREFIX               ACE_TEXT("\nld_Notice %D ")
#define ACE_WARNING_PREFIX          ACE_TEXT("\nld_Warning %D ")
#define ACE_ERROR_PREFIX                ACE_TEXT("\nld_Error %D ")
#define ACE_CRITICAL_PREFIX             ACE_TEXT("\nld_Critical %D ")
#define ACE_ALERT_PREFIX                ACE_TEXT("\nld_Alert %D ")
#define ACE_EMERGENCY_PREFIX        ACE_TEXT("\nld_Emergency %D ")

#define LD_DEBUG(FMT, ...)\
    ACE_DEBUG((LM_DEBUG, ACE_DEBUG_PREFIX  FMT __VA_ARGS__))

#define LD_INFO(FMT, ...)\
    ACE_DEBUG((LM_INFO, ACE_INFO_PREFIX FMT  __VA_ARGS__))

#define LD_NOTICE(FMT, ...)\
    ACE_DEBUG((LM_NOTICE, ACE_NOTICE_PREFIX FMT __VA_ARGS__))

#define LD_WARNING(FMT, ...)\
     ACE_DEBUG((LM_WARNING, ACE_WARNING_PREFIX FMT  __VA_ARGS__))

#define LD_ERROR(FMT, ...) \
    ACE_DEBUG((LM_ERROR,  ACE_ERROR_PREFIX FMT   __VA_ARGS__))

#define LD_CRITICAL(FMT, ...)\
    ACE_DEBUG((LM_CRITICAL,  ACE_CRITICAL_PREFIX FMT  __VA_ARGS__))

#define LD_ALERT(FMT, ...)\
    ACE_DEBUG((LM_ALERT, ACE_ALERT_PREFIX FMT   __VA_ARGS__))

#define LD_EMERGENCY(FMT, ...)\
    ACE_DEBUG((LM_EMERGENCY,ACE_EMERGENCY_PREFIX FMT __VA_ARGS__))

#define LD_TRACE(STR)\
    ACE_DEBUG((LM_DEBUG, ACE_TEXT("\n"))); ACE_TRACE(STR)

#define LD_T(STR) ACE_TEXT(STR)


#endif
=======
#define ACE_DEBUG_PREFIX 		ACE_TEXT("ld_Debug %D ")
#define ACE_INFO_PREFIX 			ACE_TEXT("ld_Info %D ")
#define ACE_NOTICE_PREFIX 		ACE_TEXT("ld_Notice %D ")
#define ACE_WARNING_PREFIX 		ACE_TEXT("ld_Warning %D ")
#define ACE_ERROR_PREFIX 		ACE_TEXT("ld_Error %D ")
#define ACE_CRITICAL_PREFIX 		ACE_TEXT("ld_Critical %D ")
#define ACE_ALERT_PREFIX 		ACE_TEXT("ld_Alert %D ")
#define ACE_EMERGENCY_PREFIX 	ACE_TEXT("ld_Emergency %D ")

#define LD_DEBUG(FMT, ...) 				\
	ACE_DEBUG((LM_DEBUG, 			\
				ACE_DEBUG_PREFIX  FMT\
				__VA_ARGS__))

#define LD_INFO(FMT, ...) 				\
	ACE_DEBUG((LM_INFO, 				\
				ACE_INFO_PREFIX FMT	\
				__VA_ARGS__))

#define LD_NOTICE(FMT, ...) 			\
	ACE_DEBUG((LM_NOTICE, 			\
				ACE_NOTICE_PREFIX FMT\
				__VA_ARGS__))

#define LD_WARNING(FMT, ...) 			\
	ACE_DEBUG((LM_WARNING, 			\
				ACE_WARNING_PREFIX FMT\
				__VA_ARGS__))

#define LD_ERROR(FMT, ...) 				\
	ACE_DEBUG((LM_ERROR, 			\
				ACE_ERROR_PREFIX FMT\
				__VA_ARGS__))

#define LD_CRITICAL(FMT, ...) 			\
	ACE_DEBUG((LM_CRITICAL, 			\
				ACE_CRITICAL_PREFIX FMT\
				__VA_ARGS__))

#define LD_ALERT(FMT, ...) 				\
	ACE_DEBUG((LM_ALERT, 			\
				ACE_ALERT_PREFIX FMT\
				__VA_ARGS__))

#define LD_EMERGENCY(FMT, ...) 		\
	ACE_DEBUG((LM_EMERGENCY, 		\
			ACE_EMERGENCY_PREFIX FMT\
			__VA_ARGS__))

#define LD_TRACE(STR) ACE_TRACE(STR)

#define LD_T(STR) ACE_TEXT(STR)
>>>>>>> 322d64b193836dac0ba7e7ddfa7aad7e5cabfe94
