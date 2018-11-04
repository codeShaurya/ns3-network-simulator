#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
  int sock;
  int a, b, c, i, sum, sub, prod, div;
  unsigned int len;
  char ch[3] = "no";
  char ch1[3];

  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket:  ");
    exit(-1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10000);
  client.sin_addr.s_addr = INADDR_ANY;

  bzero(&client.sin_zero, 0);

  len = sizeof(struct sockaddr_in);

  if ((connect(sock, (struct sockaddr *)&client, len)) == -1)
  {
    perror("connect: ");
    exit(-1);
  }

  while (1)
  {
    printf("enter two numbers : ");
    scanf("%d", &a);
    scanf("%d", &b);
    send(sock, &a, sizeof(a), 0);
    send(sock, &b, sizeof(b), 0);
    recv(sock, &sum, sizeof(sum), 0);
    recv(sock, &sub, sizeof(sub), 0);
    recv(sock, &prod, sizeof(prod), 0);
    recv(sock, &div, sizeof(div), 0);
    printf("\nsum is : %d", sum);
    printf("\nsubtraction is : %d", sub);
    printf("\nmultiplication is : %d", prod);
    printf("\ndivision is : %d", div);
    printf("\ndo you want to exit ...press 'no'\n");
    scanf("%s", ch1);
    if ((i = strcmp(ch, ch1)) == 0)
    {
      close(sock);
      exit(0);
    }
  }
  return 0;
}
