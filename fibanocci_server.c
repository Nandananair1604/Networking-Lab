#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int ssock,csock,n,i;
    struct sockaddr_in server,client;
    socklen_t len;

    int fib[100];

    ssock = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(ssock,(struct sockaddr*)&server,sizeof(server));

    listen(ssock,5);

    printf("Server waiting...\n");

    len = sizeof(client);

    csock = accept(ssock,(struct sockaddr*)&client,&len);

    recv(csock,&n,sizeof(n),0);

    printf("Received number: %d\n",n);

    fib[0] = 0;
    fib[1] = 1;

    for(i=2;i<n;i++)
    {
        fib[i] = fib[i-1] + fib[i-2];
    }

    send(csock,fib,sizeof(fib),0);

    close(csock);
    close(ssock);

    return 0;
}
