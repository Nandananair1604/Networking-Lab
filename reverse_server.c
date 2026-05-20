#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int ssock,csock;
    struct sockaddr_in server,client;
    socklen_t len;

    char str[100],rev[100];
    int i,j,n;

    ssock = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(ssock,(struct sockaddr*)&server,sizeof(server));

    listen(ssock,5);

    printf("Server waiting...\n");

    len = sizeof(client);

    csock = accept(ssock,(struct sockaddr*)&client,&len);

    recv(csock,str,sizeof(str),0);

    printf("Received string: %s\n",str);

    n = strlen(str);

    j = 0;

    for(i=n-1;i>=0;i--)
    {
        rev[j] = str[i];
        j++;
    }

    rev[j] = '\0';

    send(csock,rev,sizeof(rev),0);

    printf("Reversed string: %s\n",rev);

    close(csock);
    close(ssock);

    return 0;
}
