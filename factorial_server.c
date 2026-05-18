#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 6767

int main()
{
    int csock, ssock, n;

    struct sockaddr_in addr;
    socklen_t addrsize = sizeof(addr);

    char b[1024];

    // Create socket
    ssock = socket(AF_INET, SOCK_STREAM, 0);
    printf("Server created...\n");

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind
    bind(ssock, (struct sockaddr *)&addr, addrsize);
    printf("Binded to port %d\n", port);

    // Listen
    listen(ssock, 5);
    printf("Listening...\n");

    // Accept
    csock = accept(ssock, (struct sockaddr *)&addr, &addrsize);
    printf("Connection established...\n");

    while(1)
    {
        recv(csock, &n, sizeof(n), 0);
        printf("The number is %d\n", n);

        int fact = 1;

        // Exit condition
        if(n == -1)
        {
            printf("Exiting...\n");
            break;
        }

        // Factorial of 0
        if(n == 0)
        {
            sprintf(b, "Factorial of %d is 1\n", n);
            printf("%s", b);
            send(csock, b, strlen(b), 0);
            continue;
        }

        // Factorial calculation
        for(int i = 1; i <= n; i++)
        {
            fact = fact * i;
        }

        sprintf(b, "Factorial of %d is %d\n", n, fact);
        printf("%s", b);

        send(csock, b, strlen(b), 0);
    }

    close(csock);
    close(ssock);

    return 0;
}
