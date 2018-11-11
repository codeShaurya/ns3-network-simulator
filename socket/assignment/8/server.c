/*
    $ g++ server.c -o server
    $ ./server
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

struct student
{
  int roll;
  int m1;
  int m2;
  int m3;
  double avg;
};

void main()
{
  int ssock, csock;
  struct sockaddr_in server, client;

  struct student a[11];
  int i, n;

  unsigned int len = sizeof(struct sockaddr_in);

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Cannot create server\n");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(10000);
  bzero(&server.sin_zero, 0);

  if (bind(ssock, (struct sockaddr *)&server, len) == -1)
  {
    perror("Cannot bind\n");
    exit(-1);
  }

  if (listen(ssock, 5) == -1)
  {
    perror("Cannot listen\n");
    exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
  {
    perror("Cannot accept\n");
    exit(-1);
  }

  for (i = 1; i <= 11; i++)
  {
    a[i].roll = i;
    a[i].m1 = (i * i + 5) % 10;
    a[i].m2 = (i * i + 6) % 10;
    a[i].m3 = (i * i + 4) % 10;
    a[i].avg = (a[i].m1 + a[i].m2 + a[i].m3) / 3.0;
  }
  recv(csock, &n, sizeof(n), 0);
  send(csock, &a[n], sizeof(a[n]), 0);

  close(ssock);
}
