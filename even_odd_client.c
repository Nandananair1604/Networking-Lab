#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 6767

int main()
{
    int csock, n;

    struct sockaddr_in addr;
    char b[1024];

    csock = socket(AF_INET, SOCK_STREAM, 0);
    printf("Client created...\n");

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(csock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connected to server...\n");

    while(1)
    {
        printf("Enter number: ");
        scanf("%d", &n);

        if(n == -1)
        {
            printf("Exiting...\n");
            break;
        }

        send(csock, &n, sizeof(n), 0);

        bzero(b, 1024);

        recv(csock, b, sizeof(b), 0);

        printf("Server: %s\n", b);
    }

    close(csock);

    return 0;
}
