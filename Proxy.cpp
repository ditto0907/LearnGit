//#include "Proxy.h"

#include <stdio.h>   
#include <stdlib.h>   
#include <string.h> 

#include <iostream>
//#include <pthread.h>
//Linux socket 
  
#include <sys/types.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  


#define MAXLINE 4096

int main()
{
	int listensocket,connfd;
	char buffer[4096];
	
	struct sockaddr_in server_addr;

	bzero(&server_addr,sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(8091);

	listensocket = socket(AF_INET,SOCK_STREAM,0);
	if(listensocket<0)
	{
		printf("Creat socket failed!\n");
		exit(0);
	}
	if(bind(listensocket,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
	{
		printf("Bind socket failed\n");
		exit(0);
	}
	if(listen(listensocket,10)==-1)
	{
		printf("Listen socket failed\n");
		exit(0);
	}

	printf("======waiting for client's request======\n");
	while(1)
	{	
		connfd = accept(listensocket,(struct sockaddr*)NULL,NULL);
		int n = recv(connfd,buffer,MAXLINE,0);
		buffer[n] ='\0';
		printf("recv message:\n");
		printf("%s\n",buffer);

	}








}