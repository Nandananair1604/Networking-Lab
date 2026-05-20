#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int s,i,j,n,k=0;

    struct sockaddr_in server,client;

    socklen_t len;

    char str[100],result[100];

    s = socket(AF_INET,SOCK_DGRAM,0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(s,(struct sockaddr*)&server,sizeof(server));

    printf("Server waiting...\n");

    len = sizeof(client);

    recvfrom(s,str,sizeof(str),0,
             (struct sockaddr*)&client,&len);

    printf("Received string: %s\n",str);

    n = strlen(str);

    for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(str[i]==str[j])
            {
                str[j]=' ';
            }
        }
    }

    printf("String without duplicates: ");

    for(i=0;i<n;i++)
    {
        if(str[i]!=' ')
        {
            printf("%c",str[i]);

            result[k] = str[i];

            k++;
        }
    }

    result[k] = '\0';

    sendto(s,result,strlen(result)+1,0,
           (struct sockaddr*)&client,len);

    printf("\nString after removing duplicates: %s\n",result);

    close(s);

    return 0;
}
