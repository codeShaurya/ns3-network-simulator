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

int empl[6][3];
void in()
{
  int i;
  for (i = 0; i < 6; ++i)
  {
    empl[i][0] = 10;
    empl[i][1] = 3 + i / 2;
    empl[i][2] = 2 + i / 3;
  }
}

int main()
{
  int ssock, csock;
  int a, b;
  unsigned int len;
  struct sockaddr_in server, client;

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket: is not created");
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
    perror("accept: ");
    exit(-1);
  }

  while (1)
  {
    in();
    recv(csock, &a, sizeof(a), 0);
    recv(csock, &b, sizeof(b), 0);
    int i;
    for (i = 0; i < 3; ++i)
    {
      int x = empl[a - 1][i];
      send(csock, &x, sizeof(x), 0);
    }

    if ((empl[a - 1][1] + empl[a - 1][2]) < b)
      i = 0;
    else
      i = 1;
    send(csock, &i, sizeof(i), 0);
    printf("\n data sent ");
  }
  close(ssock);
  return 0;
}