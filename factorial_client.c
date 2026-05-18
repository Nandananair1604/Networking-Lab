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

    // Create socket
    csock = socket(AF_INET, SOCK_STREAM, 0);
    printf("Client Created...\n");

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    connect(csock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connection established...\n");

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d", &n);

        // Exit condition
        if(n == -1)
        {
            printf("Exiting...\n");
            break;
        }

        // Send number to server
        send(csock, &n, sizeof(n), 0);

        // Clear buffer
        bzero(b, 1024);

        // Receive result from server
        recv(csock, b, sizeof(b), 0);

        printf("Server: %s\n", b);
    }

    close(csock);

    return 0;
}
