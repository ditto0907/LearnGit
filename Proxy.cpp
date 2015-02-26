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
#include <unistd.h> 	//close函数
#include <netdb.h>   	//gethostbyname
#include <arpa/inet.h>	//inet_ntoa
#include <sys/select.h>	//select

#include <sys/wait.h> 
#include <sys/time.h> 

using namespace std;

void GetHostInformation(char* str,char* hostname,char* resource)
{
	char *p_head,*p_end,*res;
	int i;
	int len;
	//get host
	printf("Get host\n");
	p_head = strstr(str,"Host: ");
	if(p_head)
	{
		p_head = p_head+strlen("Host: ");
		p_end = strstr(p_head," ");
		res = new char[p_end-p_head+1];
		sscanf(p_head,"%s",res);
		strcpy(hostname,res);
	}
	//get resource
	printf("Get resource\n");
	p_head = strstr(str,"http://");
	if(p_head)
	{
		p_head = p_head+strlen("http://");
		p_head = strstr(p_head,"/");
		p_end = strstr(p_head," HTTP/");
		res = new char[p_end-p_head+1];
		sscanf(p_head,"%s",res);
		strcpy(resource,res);
	}
	//remove hostname
	printf("remove hostname\n");
	p_head = strstr(str,"http://");
	if(p_head)
	{
		for(i=0; i<strlen("http://"); i++)
		{
			*(p_head+i) = 0;
		}
		p_head = p_head+strlen("http://");
	
		len = strlen(p_head);
		for(i=0; i<len; i++)
		{
			if(*(p_head+i) == '/')
			{
				break;
			}
			*(p_head+i) = 0;
		}
		p_head = p_head+i;
		//printf("str:%s\n",str);
		//printf("p_head:%s\n",p_head);
		strcat(str,p_head);
	}
	printf("%s\n",str);

	printf("remove 1\n");
	p_head = strstr(str,"Accept-Encoding:");
	if(p_head)
	{
		for(i=0;i<strlen("Accept-Encoding:");i++)
		{
			*(p_head+i) = 0;
		}
		p_head = p_head+strlen("Accept-Encoding:");
	
		len = strlen(p_head);

		for(i=0; i<len; i++)
		{
			if(*(p_head+i) == '\n')
			{
				*(p_head+i) = 0;
				break;
			}
			*(p_head+i) = 0;
		}
		p_head = p_head+i+1;
		strcat(str,p_head);
	}
	printf("%s\n",str);
/*	printf("remove 2\n");
	p_head = strstr(str,"Cache-Control:");
	if(p_head)
	{
		for(i=0;i<strlen("Cache-Control:");i++)
		{
			*(p_head+i) = 0;
		}
		p_head = p_head+strlen("Cache-Control:");
	
		len = strlen(p_head);
		for(i=0; i<len; i++)
		{
			if(*(p_head+i) == '\n')
			{
				*(p_head+i) = 0;
				break;
			}
			*(p_head+i) = 0;
		}
		p_head = p_head+i+1;
		strcat(str,p_head);
	}*/

	//free(res);
}


#define MAXLINE 40960

int main()
{
	int listensocket,user_proxy,proxy_server;
	char buffer[40960];
	char buffer_return[409600];
	char hostname[200];
	char resource[200];
	
	struct sockaddr_in proxy_addr,server_addr;

	bzero(&proxy_addr,sizeof(proxy_addr));
	bzero(&server_addr,sizeof(server_addr));

	proxy_addr.sin_family = AF_INET;
	proxy_addr.sin_addr.s_addr = htons(INADDR_ANY);
	proxy_addr.sin_port = htons(8091);

	listensocket = socket(AF_INET,SOCK_STREAM,0);
	if(listensocket<0)
	{
		printf("Creat socket failed!\n");
		exit(0);
	}
	if(bind(listensocket,(struct sockaddr*)&proxy_addr,sizeof(proxy_addr))==-1)
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

	int port = 80;

	fd_set t_set;
	int h;
	struct timeval tv;
	{
		
	};


	while(1)
	{	
		memset(buffer, 0, 40960); 
		socklen_t len = sizeof(proxy_addr);
		printf("Listing\n");
		user_proxy = accept(listensocket,(struct sockaddr*)&proxy_addr,&len);
		int n = recv(user_proxy,buffer,MAXLINE,0);
		printf("Accepted:%d\n",n);
		//buffer[n] ='\0';
		//printf("recv message:\n");
		printf("%s\n",buffer);
			
		GetHostInformation(buffer,hostname,resource);
		//printf("hostname:%s\n",hostname);
		struct hostent *ht = NULL;
		ht = gethostbyname(hostname);
		for(int i=0;;i++)
		{
			if(ht->h_addr_list[i] != NULL)
			{
				printf("IP:%s\n",inet_ntoa(*((struct in_addr*)ht->h_addr_list[i])));
			}	
			else
				break;
		}
		
		server_addr.sin_family = AF_INET;
		memcpy(&server_addr.sin_addr.s_addr,ht->h_addr_list[0],ht->h_length);
		//server_addr.sin_addr.s_addr = inet_addr("115.239.210.26"); 
		server_addr.sin_port = htons(80);


		proxy_server = socket(AF_INET,SOCK_STREAM,0);

		if(proxy_server ==-1)
		{
			printf("Create Proxy to Server Socket Failed\n");
		}
		if(connect(proxy_server,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
		{
			printf("Connect to Server Failed\n");	
		}

		int ret = send(proxy_server,buffer,strlen(buffer)+1,0);
		printf("Send buffer:\n%s\n",buffer);



		if(ret>0)
		{
			printf("Send success:%d\n",ret);	
		}
		sleep(1);

		

		int responseLen = 0;
    	int p = 0;
    	char recv_buf[100];
    	//memset(recv_buf,0,8);
		memset(buffer_return,0,4096);

    	h=0;
		FD_ZERO(&t_set);
		FD_SET(proxy_server,&t_set);

		tv.tv_sec = 0;
		tv.tv_usec = 0;

    	h = select(proxy_server+1,&t_set,NULL,NULL,&tv);
    	if(h>0)
    	{
    		while((responseLen=recv(proxy_server,recv_buf,100,0)) == 100 && p<409600) 
	    	{
	        	//strcat(buffer_return,recv_buf);
	        	//buffer_return[p++] = recv_buf[0];
		        for(int i=0;i<100;i++)
		        {
					buffer_return[p++] = recv_buf[i];
		        }
				//cout<<buffer<<endl;
	    	}
	    	for(int i=0;i<responseLen+1;i++)
	        {
				buffer_return[p++] = recv_buf[i];
	        }
			//strcat(buffer_return,recv_buf);
			//recv(proxy_server,buffer_return,strlen(buffer_return),0);

			printf("recv success\n");

			printf("receive:%s\n",buffer_return);

			ret = send(user_proxy,buffer_return,strlen(buffer_return)+1,0);

			printf("return success:%d\n",ret);	
    	}
    	else
    	{
    		printf("Recv error\n");
    	}

		close(user_proxy);
		close(proxy_server);

	}

	close(listensocket);
	//free(hostname);

}