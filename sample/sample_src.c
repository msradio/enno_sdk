
#include <stdlib.h>
#ifdef _CRT_DBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _CRT_DBG_MAP_ALLOC
#include <stdarg.h>
#include <stdio.h>
#include <enno_api/enno_api.h>

int Gtemp = 0;
int Ghum = 0;

#ifdef _WIN32
#include <WinSock2.h>
#include <Windows.h>
#pragma comment(lib, "WS2_32.lib")

FILE * __cdecl __iob_func(void) {
	static FILE _iob[3];
	_iob[0] = *stdin;
	_iob[1] = *stdout;
	_iob[2] = *stderr;
	return _iob;
}
#else
#include <unistd.h>
#endif

int platform_init(void)
{
#ifdef _WIN32
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	SOCKET sock = 0;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		exit(0);
	}
#endif
	
#ifndef NO_SSL
	tlsio_openssl_init();
#endif
	return 0;
}

const IO_INTERFACE_DESCRIPTION* platform_get_default_tlsio(void)
{
#ifndef NO_SSL
	return tlsio_openssl_get_interface_description();
#endif
}

void platform_deinit(void)
{
#ifdef _WIN32
	(void)WSACleanup();
#endif

#ifndef NO_SSL
	tlsio_openssl_deinit();
#endif
}




static unsigned int sent_messages = 0;


static void PrintLogFunction(unsigned int options, char* format, ...)
{
	va_list args;
	va_start(args, format);
	(void)vprintf(format, args);
	va_end(args);

	if (options & LOG_LINE)
	{
		(void)printf("\r\n");
	}
}


void on_message(void *pClient, const char* topic, char* message, int length)
{
	printf("\r\nREC:  Topic=%s, Message=%s\r\n", topic, message);
}



int main(void)
{
	char* values[2];
	char value0[100];
	char value1[100];
	values[0] = value0;
	values[1] = value1;

	ENNO_CLIENT enno;
	enno.fn_log = PrintLogFunction;
	enno.on_message = on_message;		// Triger when message arivel;
	//enno.host = "shtc.wisiot.com";
	enno.host = "139.217.18.199";
	enno.port = 1883;
	enno.deviceid = "378b8cab-be2c-445a-a707-2389aad04b48";
	enno.token = "65c18662-527d-4f77-968a-302c9c55627d";
	enno.oter = "";
	enno.subscrib[0] = "enno/in/json";	// Subscrib two subjects 
	enno.subscrib[1] = "enno/out/json/378b8cab-be2c-445a-a707-2389aad04b48";

#ifdef QCC_OS_GROUP_POSIX
	airbox_init();
#endif // QCC_OS_GROUP_POSIX

	Error_t ret = enno_init(&enno);
	ret = enno_connect(&enno);
	uint64_t current_ms = 0;
	while (1)
	{
		enno_loop(&enno);
		if (enno_timeout(&enno, 4000))
		{
			float v;
#ifdef QCC_OS_GROUP_POSIX			
			airbox_loop();
			sprintf(value0, "%f", Gtemp/10.0);
			sprintf(value1, "%f", Ghum/10.0);
#else			v = rand() / 100.0;			sprintf(value0, "%f", v);			v = rand() / 10.0;			sprintf(value1, "%f", v);
#endif
			enno_publish(&enno, enno.subscrib[0], values, 2);
			printf("T=%d,H=%d \r\n", Gtemp, Ghum);
		}
#ifdef _WIN32
		Sleep(1);
#else
		usleep(1);
#endif
	}
	return 0;
}


