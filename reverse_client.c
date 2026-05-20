#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int csock;

    struct sockaddr_in server;

    char str[100],rev[100];

    csock = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);

    connect(csock,(struct sockaddr*)&server,sizeof(server));

    printf("Enter string: ");
    scanf("%s",str);

    send(csock,str,sizeof(str),0);

    recv(csock,rev,sizeof(rev),0);

    printf("Reversed string: %s\n",rev);

    close(csock);

    return 0;
}
