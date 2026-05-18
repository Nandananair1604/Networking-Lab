#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 8989

int main()
{
    int csock, n;

    struct sockaddr_in addr;
    socklen_t addrsize = sizeof(addr);

    char b[1024];

    // Create UDP socket
    csock = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Client created\n");

    // Initialize structure
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while(1)
    {
        printf("Enter the number: ");
        scanf("%d", &n);

        // Send number to server
        sendto(csock,
               &n,
               sizeof(n),
               0,
               (struct sockaddr *)&addr,
               addrsize);

        // Exit condition
        if(n == -1)
        {
            printf("Exiting...\n");
            break;
        }

        // Clear buffer
        bzero(b, 1024);

        // Receive result from server
        recvfrom(csock,
                 b,
                 sizeof(b),
                 0,
                 (struct sockaddr *)&addr,
                 &addrsize);

        printf("Server says: %s\n", b);
    }

    close(csock);

    return 0;
}
