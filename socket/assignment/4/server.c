/*
    $ g++ server.c -o server
    $ ./server
*/

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
  int ssock, csock;
  int a, b;
  int sum, sub, prod, div;
  unsigned int len;
  struct sockaddr_in server, client;
  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket is not created");
    exit(-1);
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(10000);
  server.sin_addr.s_addr = INADDR_ANY;

  bzero(&server.sin_zero, 0);

  len = sizeof(struct sockaddr_in);

  if ((bind(ssock, (struct sockaddr *)&server, len)) == -1)
  {
    perror("bind: ");
    exit(-1);
  }

  if ((listen(ssock, 5)) == -1)
  {
    perror("listen: ");
    exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &len)) == -1)
  {
    perror("accept:  ");
    exit(-1);
  }

  while (1)
  {
    recv(csock, &a, sizeof(a), 0);
    recv(csock, &b, sizeof(b), 0);
    sum = a + b;
    sub = a - b;
    prod = a * b;
    div = a / b;
    send(csock, &sum, sizeof(sum), 0);
    send(csock, &sub, sizeof(sub), 0);
    send(csock, &prod, sizeof(prod), 0);
    send(csock, &div, sizeof(div), 0);
    printf("Done\n");
  }

  close(ssock);
  return 0;
}
