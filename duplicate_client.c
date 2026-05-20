#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int s;

    struct sockaddr_in server;

    socklen_t len=sizeof(server);

    char str[100],result[100];

    s=socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family=AF_INET;
    server.sin_port=htons(8080);

    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);

    printf("Enter string: ");
    scanf("%s",str);

    sendto(s,str,sizeof(str),0,
           (struct sockaddr*)&server,len);

    recvfrom(s,result,sizeof(result),0,
             NULL,NULL);

    printf("String after removing duplicates: %s\n",result);

    close(s);

    return 0;
}
