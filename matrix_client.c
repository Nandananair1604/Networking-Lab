#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    int A[2][2], B[2][2], C[2][2];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter Matrix A (2x2):\n");
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            scanf("%d",&A[i][j]);

    printf("Enter Matrix B (2x2):\n");
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            scanf("%d",&B[i][j]);

    send(sock, A, sizeof(A), 0);
    send(sock, B, sizeof(B), 0);

    recv(sock, C, sizeof(C), 0);

    printf("\nResult Matrix from Server:\n");

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
            printf("%d ",C[i][j]);
        printf("\n");
    }

    close(sock);

    return 0;
}
