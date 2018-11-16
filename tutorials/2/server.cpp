/*
    $ g++ server.c -o server
    $./server
*/
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

struct item
{
  char s[100];
  char n[100];
};

bool strcomp(char a[], char s[])
{
  int l = strlen(s);
  int b = strlen(a);
  if (l != b)
    return 1;
  for (int i = 0; i < l; i++)
  {
    if (a[i] != s[i])
      return 1;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  int ssock, csock;
  FILE *f;
  struct item a;
  int i = 0, n = 0;
  unsigned int len;
  char q[100];

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

  recv(csock, &q, sizeof(q), 0);

  f = fopen("city.txt", "r");
  while (fscanf(f, "%s %s ", &a.s, &a.n) != EOF)
  {
    cout << a.s << "  " << a.n << endl;
    if (strcomp(a.s, q) == 0)
    {
      n = 1;
      cout << "matcj";
      printf("%s", a.n);
      break;
    }
  }

  send(csock, &n, sizeof(n), 0);
  send(csock, &a.n, sizeof(a.n), 0);

  return 0;
}
