#ifndef __PROXY_H__
#define __PROXY_H__

#include <stdio.h>   
#include <stdlib.h>   
#include <string.h> 

#include <iostream>
#include <pthread.h>
//Linux socket 
#include <netinet/in.h>   
#include <sys/types.h>   
#include <sys/socket.h>   


#define default_port 8090

/*public class Proxy
{
public:
	Proxy();
	~Proxy();

	struct ProxySockets
	{
		socket ProxyToUserSocket;		//本地到PROXY服务器的socket
		socket ProxyToServerSocket;		//PROXY服务器到远程主机的socket
		bool IsProxyToServerClosed;		//本地机器到PROXY
		bool IsProxyToServClosed;		//PROXY服务器到远程主机状态
	};
	struct ProxyParam
	{
		char Address[256];				//远程主机地址
		int IsConnectedOK;				//Proxy服务器到远程主机的链接状态
		ProxySockets* pPair;			//维护一组SOCKET的指针
		int Port;						//用来连接远程主机的端口				
	};
	//socket listensocket;

	int StartProxyServer();

	int ResolveInformation(char* str,char* address,int* port);

	int UserToProxy(void* pParam);

	int ProxyToServer(void* pParam);

};*/



#endif