#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    int A[2][2], B[2][2], C[2][2];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    listen(server_fd, 3);

    printf("Server waiting for connection...\n");

    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    recv(new_socket, A, sizeof(A), 0);
    recv(new_socket, B, sizeof(B), 0);

    printf("\nMatrix A:\n");
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
            printf("%d ",A[i][j]);
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
            printf("%d ",B[i][j]);
        printf("\n");
    }

    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
        {
            C[i][j] = 0;
            for(int k=0;k<2;k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }

    printf("\nResult Matrix:\n");
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<2;j++)
            printf("%d ",C[i][j]);
        printf("\n");
    }

    send(new_socket, C, sizeof(C), 0);

    close(new_socket);
    close(server_fd);

    return 0;
}
