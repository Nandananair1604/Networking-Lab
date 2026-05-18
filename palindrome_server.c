#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define port 3036
void main()
{
int csock, ssock;
char b[1024], str[1024];
struct sockaddr_in addr;
socklen_t addrsize = sizeof(addr);

ssock=socket(AF_INET, SOCK_STREAM, 0);
printf("Server created .. \n");

memset(&addr,0, sizeof(addr));
addr. sin_family=AF_INET;
addr. sin_port=htons(port);
addr.sin_addr.s_addr=inet_addr("127.0.0.1");

bind(ssock,(struct sockaddr *)&addr,sizeof(addr));
printf("Binded to port %d\n", port);

listen(ssock, 5);
printf("Listnening ... \n");

csock=accept(ssock, (struct sockaddr *)&addr, &addrsize);
printf("Client Connected\n");

bzero(str, 1024);
recv(csock, str, sizeof(str), 0);
printf("String: %s\n",str);

int is_palindrome=1;
for(int i=0;i <= strlen(str)/2;i++)
{
if(str[i] != str[strlen(str)-1-i])

is_palindrome=0;
break;
}
if(is_palindrome)
{
sprintf(b, "palindrome\n");
printf("%s is palindrome", str);
}
else
{

sprintf(b, "Not palindrome");
printf("%s is not a palindrome", str);
}
send(csock, b, strlen(b), 0);
close(csock);
close(ssock);
}
