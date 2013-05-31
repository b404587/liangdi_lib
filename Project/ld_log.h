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
如果定义了预处理器宏ACE_NDEBUG,
ACE_DEBUG会展开为一个空行
*/

/*
ACE日志格式化指令
格式代码        参数类型        显示
A:                              ACE_timer_t            浮点数
a:                              -                            在显示输出后中止程序
c:                              char                        单个字符
C:                              char*                       字符串(窄字符)
i,d:                            int                         十进制数
I:                              -                           根据ACE_Trace::get_nesting_indent()获得的嵌套深度缩进输出
e,E,f,F,g,G:                double                  双精度浮点数
l:                              -                           日志宏出现之处的行号
M:                           -                              消息严重级别的文本形式
m:                          -                               与errno值对应的信息，和strerror()所做的事情一样
N:                           -                              日志宏所在文件的名称
n:                           -                              传给ACE_Log_Msg::open()的程序名
o:                          int                             八进制数
P:                           -                              当前进程的ID
p:                           ACE_TCHAR*             指定的字符串，接着是适当的error消息，和perror所做的事情一样
Q:                           ACE_UINT64            十进制数
r:                          void(*)()                   无显示，调用指定的函数
R:                           int                            十进制数
S:                           int                            编写好的信号的名称
s:                          ACE_TCHAR*              字符串，取决于ACE_TCHAR类型，窄的或者宽的
T:                          -                                   当前时间，格式是hour:minute:sec.usec
D:                            -                                 时间戳，格式是month/day/year/ hour:minute:sec.usec
t:                           -                                  调用线程的(calling thread)ID(如果是单线程就是1)
u:                            int                               无符号十进制数
w:                            wchar_t                   单个宽字符
W:                         wchar_t*                     宽字符串
x,X:                        int                             十六进制数
@:                           void*                      以十六进制表示的指针值
%:                           N/A                            单个百分号:"%"
*/

/*
ACE日志宏
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
日志宏是否产生方法调用，取决于编译宏选项:
ACE_NTRACE
ACE_NDEBUG
ACE_NLOGGING
例如，define ACE_NTRACE 1 禁用日志，#define ACE_NTRACE 0 启用
注意，ACE_TRACE 取决于ACE_NTRACE 和ACE_NDEBUG两个配置
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
