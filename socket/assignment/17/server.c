#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

struct item
{
  int id;
  char n[100];
  int p;
  int q;
};

int main(int argc, char *argv[])
{
  int ssock, csock;
  FILE *f;
  struct item a;
  int i = 0, n = -1;
  unsigned int len;
  int item_id, q;

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

  recv(csock, &item_id, sizeof(item_id), 0);
  recv(csock, &q, sizeof(q), 0);

  f = fopen("item.txt", "r");
  while (fscanf(f, "%d %s %s %d", &a.id, &a.n, &a.p, &a.q) != EOF)
  {
    if (a.id == item_id)
    {
      if (a.q >= q)
        n = 1;
      break;
    }
  }
  send(csock, &n, sizeof(n), 0);

  return 0;
}
