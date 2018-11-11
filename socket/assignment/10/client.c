/*
$ g++ client.c -o client
$ ./client
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
  int sock;
  int a, c, b;
  unsigned int len;
  char ch[4];
  struct sockaddr_in client;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket: ");
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
    printf("enter your id :\n");
    scanf("%d", &a);
    printf("enter no of leaves you want :\n");
    scanf("%d", &c);

    send(sock, &a, sizeof(a), 0);
    send(sock, &c, sizeof(c), 0);

    recv(sock, &b, sizeof(b), 0);
    printf("\nTotal leaves provided to you is: %d\n", b);

    recv(sock, &b, sizeof(b), 0);
    printf("\nBalance leave : %d", b);

    recv(sock, &b, sizeof(b), 0);
    printf("\nExtra leaves that can be provided is: %d\n", b);

    recv(sock, &b, sizeof(b), 0);
    if (b == 0)
      printf("\nNo more leaves :(\n");
    else
      printf("\nhurrey ! leave granted:)\n");

    printf("if you want to exit...press 'yes'\n");
    scanf("%s", ch);
    if (strcmp(ch, "yes") == 0)
    {
      close(sock);
      exit(0);
    }
  }
  return 0;
}