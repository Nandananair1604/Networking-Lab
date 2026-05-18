#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#define port 3036
int main()
{
        int csocket;
        struct sockaddr_in addr;
        char b[1024],str[1024];
        socklen_t addrsize=sizeof(addr);
        csocket=socket(AF_INET,SOCK_STREAM,0);
        if(csocket<0)
        {
        printf("not created");
        }
        memset(&addr,0,sizeof(addr));
        addr.sin_family=AF_INET;
        addr.sin_port=htons(port);
        addr.sin_addr.s_addr=inet_addr("127.0.0.1");

        connect(csocket,(struct sockaddr *)&addr,sizeof(addr));
        printf("connected");


        printf("enter the string");
        scanf("%s",str);

        send(csocket,str,strlen(str),0);
        bzero(b,1024);
        recv(csocket,b,sizeof(str),0);
        printf("%s",b);
        close(csocket);
return 0;
