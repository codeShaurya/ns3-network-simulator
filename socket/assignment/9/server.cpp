#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

int main()
{
  int ssock, csock;
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
    char s[10000], ans;
    int n, f = 0, m = INT_MIN;
    int v[26] = {0};

    recv(csock, &s, sizeof(s), 0);
    recv(csock, &n, sizeof(n), 0);

    for (int j = 0; j < strlen(s); j++)
      v[s[j] - 'a']++;

    for (int j = 0; j < 26; j++)
    {
      if (v[j] == n)
      {
        f = 1;
        ans = j + 'a';
        break;
      }
      else if (v[j] > m)
      {
        m = v[j];
        ans = j + 'a';
      }
    }

    send(csock, &f, sizeof(f), 0);
    send(csock, &ans, sizeof(ans), 0);
  }

  close(ssock);
  return 0;
}