// ClientGroup.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <WinSock2.h>   
#include <MSWSock.h>   
#include <Windows.h>   
#include <process.h>  
unsigned __stdcall ThreadProc(LPVOID lParam); 
unsigned __stdcall ThreadSend(LPVOID lParam);
#define  MAX_THREAD 10
HANDLE hThread[MAX_THREAD] = {0};  
int flag = 0;

SOCKET sockc[2048] = {0};
SOCKET sockc1[1024] = {0};
struct sock
{
	int a;
	int b;
	long port;
};
int main(int argc, char* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	
	wVersionRequested = MAKEWORD( 1, 1 );
	
	err = WSAStartup( wVersionRequested, &wsaData );
	if ( err != 0 ) {
		return 0;
	}
	
	if ( LOBYTE( wsaData.wVersion ) != 1 ||
		HIBYTE( wsaData.wVersion ) != 1 ) {
		WSACleanup();
		return 0; 
	}
	int i;
	int a = 0, b= 0;

	int para = 512;
	hThread[0] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *) (void *))ThreadProc,(void *)para, 0, NULL);

//	hThread[1] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *) (void *))ThreadProc,(void *)para, 0, NULL);
	hThread[9] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *) (void *))ThreadSend,(void *)sockc,0,NULL);
	///hThread[2] = (HANDLE)_beginthreadex(NULL, 0, (unsigned (__stdcall *) (void *))ThreadProc,(void *)co, 0, NULL);
	
	SOCKADDR_IN addrSrv;
	for (i = 0; i<200; i++)
	{
			sockc[i] = socket(AF_INET, SOCK_STREAM, 0);
			addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
			addrSrv.sin_family = AF_INET;
			int port = 5053;
			int count  = 200;
			if (i > count)
			{
				count = count +200;
				port = port+1;
			}
			addrSrv.sin_port = htons(port);
			int ret = connect(sockc[i], (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
		//select()
		//Sleep(1000);

		if(ret == -1)
			{
				a++;
				printf("连接失败= %d , 失败总数：%d\n", i, a);
				
			}
			else
			{
				b++;
				printf("连接成功= %d ,成功总数：%d\n", i, b);
			}
	
	}
	Sleep(10000);

	for (i = 0; i<1024; i++)
	{
		closesocket(sockc[i]);
	}
	Sleep(10);
	//socket()
	printf("Hello World!\n");
	return 0;
}

unsigned __stdcall ThreadProc(LPVOID lParam)  
{
	int* cout = (int*)lParam;
	//SOCKET sock[10];
	
	for (int i = 200; i < *cout; i++)
	{
		sockc1[i] = socket(AF_INET, SOCK_STREAM, 0);
		SOCKADDR_IN addrSrv;
		addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		addrSrv.sin_family = AF_INET;
		addrSrv.sin_port = htons(5050);
		if (connect(sockc1[i], (SOCKADDR *) &addrSrv, sizeof(SOCKADDR)))
		{
			printf("failed socket %d \n", i+1);
		}
		send(sockc1[i], "12 12", 10, 0);
	}
	return 0;
}

unsigned __stdcall ThreadSend(LPVOID lParam)
{
//	SOCKET* psock = (SOCKET*) lParam;
		while (1)
		{
			for (int i= 0; i < 1024; i++)
			{
				if (sockc != 0)
				{
					send(sockc[i], "111111111", 256, 0);
				}				
			}
			Sleep(1000);
		}	
	return 0;
}