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
  int n = 0;
  unsigned int len;
  int q;

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

  f = fopen("book.txt", "r");
  cout << q << endl;
  int p, o, i, r;
  int ans = 0;
  char t[100], w[100], y[100];
  while (fscanf(f, "%d %s %s %s %d %d %d", &p, &w, &t, &y, &o, &i, &r) != EOF)
  {
    cout << p << " " << w << " " << t << " " << y << " " << o << " " << i << r << endl;
    if (q == i)
    {
      cout << "book found";
      ans = 1;
      break;
    }
  }

  send(csock, &ans, sizeof(ans), 0);
  send(csock, &p, sizeof(p), 0);
  send(csock, &w, sizeof(w), 0);
  send(csock, &t, sizeof(t), 0);
  send(csock, &y, sizeof(y), 0);
  send(csock, &o, sizeof(o), 0);
  send(csock, &i, sizeof(i), 0);
  send(csock, &r, sizeof(r), 0);

  return 0;
}
