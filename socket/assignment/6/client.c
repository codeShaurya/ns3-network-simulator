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
  int a, b, c, i;
  unsigned int len;
  char ch[3] = "no";
  char ch1[3];

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
  b = 0;
  while (1)
  {
    printf("enter the number:\n");
    scanf("%d", &a);
    if (b != 0)
    {
      if (a != b + 1)
      {
        printf("Wrong integer input, exiting");
        close(sock);
        exit(1);
      }
    }
    else if (b == 0)
    {
      if (!(a == 0 || a == 1))
      {
        printf("Wrong integer input, exiting");
        close(sock);
        exit(1);
      }
    }
    send(sock, &a, sizeof(a), 0);
    b = a;
    if (a == 4)
      b = 0;
    recv(sock, &c, sizeof(c), 0);
    printf("received number is %d\n", c);
  }
  return 0;
}
