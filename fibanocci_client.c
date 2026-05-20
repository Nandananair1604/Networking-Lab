#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int csock,n,i;

    struct sockaddr_in server;

    int fib[100];

    csock = socket(AF_INET,SOCK_STREAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);

    connect(csock,(struct sockaddr*)&server,sizeof(server));

    printf("Enter number of terms: ");
    scanf("%d",&n);

    send(csock,&n,sizeof(n),0);

    recv(csock,fib,sizeof(fib),0);

    printf("Fibonacci series:\n");

    for(i=0;i<n;i++)
    {
        printf("%d ",fib[i]);
    }

    printf("\n");

    close(csock);

    return 0;
}
