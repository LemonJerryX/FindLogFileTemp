#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
# define OS_WINDOWS
#elif defined(__CYGWIN__) || defined(__CYGWIN32__)
# define OS_CYGWIN
#elif defined(linux) || defined(__linux) || defined(__linux__)
# define OS_LINUX
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__)
# define OS_MACOSX
#elif defined(__FreeBSD__)
# define OS_FREEBSD
#elif defined(__NetBSD__)
# define OS_NETBSD
#elif defined(__OpenBSD__)
# define OS_OPENBSD
#else
// TODO(hamaji): Add other platforms.
#endif

#if defined(OS_LINUX)
#include <dlfcn.h>
#endif

//LOG_ 日志输出级别
#define LOG_INFO		0	//信息
#define LOG_WARNING		1	//警告
#define LOG_ERROR		2	//错误
#define LOG_FATAL		3	//严重错误，触发中断结束进程

#if defined(OS_LINUX)
#define COMPACT_GOOGLE_LOG_INFO( ...) GLog()(LOG_INFO, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define COMPACT_GOOGLE_LOG_WARNING( ...) GLog()(LOG_WARNING,__FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define COMPACT_GOOGLE_LOG_ERROR( ...) GLog()(LOG_ERROR, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define COMPACT_GOOGLE_LOG_FATAL( ...) GLog()(LOG_FATAL, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else
#define COMPACT_GOOGLE_LOG_INFO(format, ...) GLog()(LOG_INFO, __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__)
#define COMPACT_GOOGLE_LOG_WARNING(format, ...) GLog()(LOG_WARNING,__FILE__, __LINE__, __FUNCTION__,  format, __VA_ARGS__)
#define COMPACT_GOOGLE_LOG_ERROR(format, ...) GLog()(LOG_ERROR, __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__)
#define COMPACT_GOOGLE_LOG_FATAL(format, ...) GLog()(LOG_FATAL, __FILE__, __LINE__, __FUNCTION__, format, __VA_ARGS__)
#endif


//日志最大长度超过30000字节时自动截断
#define LOG(severity, format, ...) COMPACT_GOOGLE_ ## severity(format, __VA_ARGS__)



/*
//Example
LOG(LOG_INFO, "Hello glog");
LOG(LOG_INFO, "Total number of files:%d", 100);
LOG(LOG_WARNING, "Connection to server timed out, error:%d", 10094);
LOG(LOG_ERROR, "Fail to open file, file name:%s", "123.txt");
*/

/*
GlogConfig.ini 配置说明
[LOG]
;是否写入日志：0不开启，1开启，默认0
writelog=0

;日志输出级别：0信息，1警告，2错误，3严重错误，默认1
minlevel=1

;日志文件路径类型：0当前进程路径，1集中输出 "%ALLUSERSPROFILE%\deck\log\processName.exe.log"，默认0
dirType=0
*/

class GLog
{
	typedef int (*WriteLogAPtr)(int severity, const char *file, int line, const char *function, const char* format, va_list args);
	typedef int (*WriteLogWPtr)(int severity, const char *file, int line, const char *function, const wchar_t* format, va_list args);
public:
	explicit GLog()
	{

	}

	void Init(WriteLogAPtr *pWriteLogA, WriteLogWPtr *pWriteLogW) const 
	{
		static WriteLogAPtr WriteLogA = NULL;
		static WriteLogWPtr WriteLogW = NULL;
#if defined(OS_LINUX)
		//open the lib
		static void *handle = dlopen("libglog.so", RTLD_NOW);
		if(handle == NULL)
		{  
			return ;
		}

		//clear error info
		//char *err = dlerror();
		if(WriteLogA == NULL)
		{
			WriteLogA = (WriteLogAPtr)dlsym(handle, "WriteLogA");
			//err = dlerror();
		}

		if(WriteLogW == NULL)
		{
			WriteLogW= (WriteLogWPtr)dlsym(handle, "WriteLogW");
			//err = dlerror();
		}
#elif defined(OS_WINDOWS)
		static HMODULE hModule = (HMODULE)0xFFFFFFFF;
		if(hModule == (HMODULE)0xFFFFFFFF)
		{
#if defined(_X86_)
			TCHAR *dllPath[] = 
			{
				TEXT("vGlog.dll"), 
				TEXT(".\\vGlog.dll"),
			};
#else
			TCHAR *dllPath[] = 
			{
				TEXT("vGlog64.dll"), 
				TEXT(".\\vGlog64.dll"),
			};
#endif

			for(int i = 0; i < _countof(dllPath); i++)
			{
				hModule = LoadLibrary(dllPath[i]);
				if(hModule != NULL)
				{
					break;
				}
			}
		}

		if(hModule == NULL || hModule == (HMODULE)0xFFFFFFFF)
		{
			return;
		}

		if(WriteLogA == NULL)
		{
			WriteLogA = (WriteLogAPtr)GetProcAddress(hModule, "WriteLogA");
		}

		if(WriteLogW == NULL)
		{
			WriteLogW= (WriteLogWPtr)GetProcAddress(hModule, "WriteLogW");
		}
#elif
#  error Unsupported platform
#endif

		if(pWriteLogA != NULL)
		{
			*pWriteLogA = WriteLogA;
		}

		if(pWriteLogW != NULL)
		{
			*pWriteLogW = WriteLogW;
		}
	}

	void operator()(int severity, const char *file, int line, const char *function, const char *format, ...) const 
	{
		WriteLogAPtr WriteLogA = NULL;
		Init(&WriteLogA, NULL);
		if(WriteLogA != NULL)
		{
			va_list args;
			va_start(args, format);
			WriteLogA(severity, file, line, function, format, args);
			va_end(args);
		}
	}

	void operator()(int severity, const char *file, int line, const char *function, const wchar_t *format, ...) const 
	{
		WriteLogWPtr WriteLogW = NULL;
		Init(NULL, &WriteLogW);
		if(WriteLogW != NULL)
		{
			va_list args;
			va_start(args, format);
			WriteLogW(severity, file, line, function, format, args);
			va_end(args);
		}
	}
};