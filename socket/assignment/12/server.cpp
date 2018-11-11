#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

bool strcomp(char a[], string s)
{
  int l = s.length();
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

int main()
{
  int ssock, csock;
  int i = 0, n;
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

    char s[1000], z[1000];
    string q, a;
    int ans = 0;
    char nf[20] = "No result";
    recv(csock, &s, sizeof(s), 0);
    ifstream data("answer.txt");

    while (getline(data, q))
    {
      getline(data, a);
      if (strcomp(s, q) == 0)
      {
        ans = 1;
        break;
      }
    }

    for (int i = 0; i < a.length(); i++)
      z[i] = a[i];

    if (ans == 0)
      send(csock, &nf, sizeof(nf), 0);
    else
      send(csock, &z, sizeof(z), 0);
  }

  close(csock);
  return 0;
}
