#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 6767

int main()
{
    int ssock, csock, n;

    struct sockaddr_in addr;
    socklen_t addrsize = sizeof(addr);

    char b[1024];

    ssock = socket(AF_INET, SOCK_STREAM, 0);
    printf("Server created...\n");

    memset(&addr, 0, sizeof(addr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(ssock, (struct sockaddr *)&addr, addrsize);
    printf("Binded to port %d\n", port);

    listen(ssock, 5);
    printf("Listening...\n");

    csock = accept(ssock, (struct sockaddr *)&addr, &addrsize);
    printf("Client connected...\n");

    while(1)
    {
        recv(csock, &n, sizeof(n), 0);
        printf("Number received: %d\n", n);

        if(n == -1)
        {
            printf("Exiting...\n");
            break;
        }

        int even_sum = 0, odd_sum = 0;

        for(int i = 1; i <= n; i++)
        {
            if(i % 2 == 0)
                even_sum += i;
            else
                odd_sum += i;
        }

        sprintf(b,
                "Sum of even = %d, Sum of odd = %d\n",
                even_sum,
                odd_sum);

        printf("%s", b);

        send(csock, b, strlen(b), 0);
    }

    close(csock);
    close(ssock);

    return 0;
}
