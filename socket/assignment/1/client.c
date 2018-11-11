#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
    $ g++ client.c -o client
    $ ./client
*/

int main()
{
  int sock;
  int i;
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
    int n;
    printf("enter  :\n");
    scanf("%d", &n);
    send(sock, &n, sizeof(n), 0);
    int iter = 0;
    int c;
    recv(sock, &c, sizeof(c), 0);
    printf("Tne nth fibonacci is: %d ", c);
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