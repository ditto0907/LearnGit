#include <stdio.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <time.h> 
#include <errno.h> 
#include <signal.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/wait.h> 
#include <sys/time.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 

#define IPSTR "115.239.210.26" 
#define PORT 80 
#define BUFSIZE 4092 

int main(int argc, char *argv[]) 
{

     int sockfd, ret, i, h; 
     struct sockaddr_in servaddr; 
     char str1[4096], buf[BUFSIZE], *str; 
     socklen_t len; 
     fd_set t_set1; 
     struct timeval tv; 

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 

              printf("socket error!\n"); 

               exit(0);
        }; 

  

        bzero(&servaddr, sizeof(servaddr)); 
        servaddr.sin_family = AF_INET; 
        servaddr.sin_port = htons(PORT); 

      if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 )
     
      { 
     
          printf("inet_pton error!\n"); 
          exit(0); 

       }
     
        if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) 
       {     
                printf("connect error!\n"); 
                exit(0); 
       } 
                printf("connect success \n"); 

       memset(str1, 0, 4096); 
       strcat(str1, "GET / HTTP/1.0\r\n"); 
       strcat(str1, "Accept: */*\r\n"); //image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, 
       strcat(str1, "Accept-Language: cn\r\n"); 
       strcat(str1, "User-Agent: Mozilla/4.0\r\n");
       strcat(str1, "Host: www.baidu.com\r\n"); 
       strcat(str1,"Connection: Keep-Alive\r\n");
       strcat(str1, "\r\n\r\n"); 
        printf("%s\n",str1); 

       ret = send(sockfd,(void *)str1,strlen(str1),0); 
       if (ret < 0) { 
                printf("send error %d，Error message'%s'\n",errno, strerror(errno)); 
                exit(0); 

        }else{ 

                printf("send success ,total send %d \n", ret); 
        } 


     while(1){ 
   
                sleep(2); 
                printf("******\n");
                tv.tv_sec= 0; 
                tv.tv_usec= 0; 

                h= 0; 
                          FD_ZERO(&t_set1); 

                           FD_SET(sockfd, &t_set1); 
                printf("--------------->1\n"); 
                h= select(sockfd +1, &t_set1, NULL, NULL, &tv); 
                 
                printf("h = %d\n",h);
                printf("--------------->2\n"); 
               
                if (h == 0) continue; 
                if (h < 0) { 
                         close(sockfd); 
                       printf("some thing read error！\n"); 
                       return -1; 

                 }; 
    
                if (h > 0){ 
                        memset(buf, 0, 4095); 
                        i= recv(sockfd, (void *)buf, 4092,0); 
                        printf("i = %d\n",i); 
                          if (i==0){ 

                               close(sockfd); 
                               printf("read message find error,stop!\n"); 
                               return -1; 

                       } 

                   printf("%s\n", buf); 

                 } 

         } 

         close(sockfd); 
         return 0; 
}





strcat(str1, "GET ");
strcat(str1, resource);
strcat(str1, " HTTP/1.1\r\n");
strcat(str1, "Host: "); 
strcat(str1, hostname);strcat(str1, "\r\n"); 
strcat(str1, "Proxy-Connection: Keep-Alive\r\n");
//strcat(str1, "Cache-Control text/html,application/xhtmlml,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");
strcat(str1, "User-Agent: Mozilla/4.0\r\n");
//strcat(str1, "User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/40.0.2214.111 Safari/537.36\r\n");
//strcat(str1, "Accept-Encoding: gzip, deflate, sdch\r\n");
strcat(str1, "Accept: */*\r\n"); //image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, 
strcat(str1, "Accept-Language: cn\r\n");
//strcat(str1, "Accept-Language: en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4\r\n"); 
//strcat(str1, "Cookie: BD_UPN=123353; __utmt=1; __utma=51854390.835701231.1424838232.1424919853.1424924045.4; __utmb=51854390.2.10.1424924045; __utmc=51854390; __utmz=51854390.1424838232.1.1.utmcsr=(direct)|utmccn=(direct)|utmcmd=(none); __utmv=51854390.000--|3=entry_date=20150225=1\r\n");
strcat(str1, "\r\n\r\n"); 
printf("%s\n",str1);




char str1[4096];
memset(str1, 0, 4096); 
strcat(str1, "GET ");
strcat(str1, resource);
strcat(str1, " HTTP/1.0\r\n");
strcat(str1, "Host: "); 
strcat(str1, hostname);
strcat(str1, "\r\n"); 
strcat(str1, "Proxy-Connection: Keep-Alive\r\n");

strcat(str1, "Cache-Control text/html,application/xhtmlml,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n");

//strcat(str1, "User-Agent: Mozilla/4.0\r\n");
strcat(str1, "User-Agent: Mozilla/5.0 (X11; Linux i686) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/40.0.2214.111 Safari/537.36\r\n");

//strcat(str1, "Accept-Encoding: gzip, deflate, sdch\r\n");

strcat(str1, "Accept: */*\r\n"); //image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/vnd.ms-excel, application/msword, application/vnd.ms-powerpoint, 

strcat(str1, "Accept-Language: en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4\r\n"); 

strcat(str1, "\r\n\r\n"); 
//printf("%s\n",str1);
//int ret = send(proxy_server,str1,strlen(str1),0);