#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
    $ g++ server.c -o server
    $ ./server
*/

int main()
{
  int ssock, csock;
  int a, i, t = 0;
  int v[100];
  unsigned int len;
  struct sockaddr_in server, client;
  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("error");
    exit(-1);
  }

  for (i = 0; i < 100; i++)
    v[i] = -1;

  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&server.sin_zero, 0);

  len = sizeof(struct sockaddr_in);
  if ((bind(ssock, (struct sockaddr *)&server, len)) == -1)
  {
    perror("error bind");
    exit(-1);
  }
  if ((listen(ssock, 5)) == -1)
  {
    perror("error listen");
    exit(-1);
  }
  if ((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
  {
    perror("error accept");
    exit(-1);
  }

  while (1)
  {
    recv(csock, &a, sizeof(a), 0);
    memset(v, -1, sizeof(v));
    for (i = 2; i <= a; i++)
    {
      while (a % i == 0)
      {
        a /= i;
        v[t] = i;
        t++;
      }
    }
    send(csock, v, sizeof(v), 0);
    printf("\nsent\n");
  }

  close(ssock);
  return 0;
}