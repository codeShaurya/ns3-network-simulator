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
  int a, i, j;
  int v[1000][1000] = {0};
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
    printf("client sent : %d", a);
    for (i = 0; i < a; i++)
    {
      for (j = i; j < 2 * a - 1 - i; j += 2)
      {
        v[i][j] = 1;
      }
    }
    send(csock, &v, sizeof(v), 0);
    printf("pattern is printed on client\n");
  }

  close(ssock);
  return 0;
}
