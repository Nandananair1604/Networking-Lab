#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 8989

int main()
{
    int ssock, n;

    struct sockaddr_in addr;
    socklen_t addrsize = sizeof(addr);

    char b[1024];

    // Create UDP socket
    ssock = socket(AF_INET, SOCK_DGRAM, 0);

    printf("Server created successfully\n");

    // Initialize structure with zeros
    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket
    bind(ssock,
         (struct sockaddr *)&addr,
         addrsize);

    printf("Binded to port %d\n", port);

    while(1)
    {
        // Receive number from client
        recvfrom(ssock,
                 &n,
                 sizeof(n),
                 0,
                 (struct sockaddr *)&addr,
                 &addrsize);

        printf("Number is %d\n", n);

        // Exit condition
        if(n == -1)
        {
            printf("Exiting...\n");
            break;
        }

        int is_prime = 1;

        // Special case
        if(n <= 1)
        {
            sprintf(b,
                    "%d is neither prime nor composite\n",
                    n);

            printf("%s", b);

            sendto(ssock,
                   b,
                   strlen(b),
                   0,
                   (struct sockaddr *)&addr,
                   addrsize);

            continue;
        }

        // Prime checking loop
        for(int i = 2; i <= n/2; i++)
        {
            if(n % i == 0)
            {
                is_prime = 0;
                break;
            }
        }

        // Result
        if(is_prime)
        {
            sprintf(b, "%d is prime\n", n);

            printf("%s", b);
        }
        else
        {
            sprintf(b, "%d is composite\n", n);

            printf("%s", b);
        }

        // Send result to client
        sendto(ssock,
               b,
               strlen(b),
               0,
               (struct sockaddr *)&addr,
               addrsize);
    }

    close(ssock);

    return 0;
}
