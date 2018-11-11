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
    $ g++ server.c -o server
    $ ./server
*/

char Grade(int n)
{
  if (n >= 85)
    return 'A';
  else if (n >= 70)
    return 'B';
  else if (n >= 60)
    return 'C';
  else if (n >= 50)
    return 'D';
  else
    return 'F';
}

int main()
{
  int ssock, csock;
  int a, b;
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
    char c = Grade(a);
    send(csock, &c, sizeof(c), 0);
    printf("\nthe grade is = : %c\n", c);
  }

  close(ssock);
  return 0;
}
