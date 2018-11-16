/*
    $ g++ client.c -o client
    $./client
*/
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main(int argc, char *argv[])
{
  int sock;
  int n = 0;
  unsigned int len;
  int q;

  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket: ");
    exit(-1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10000);
  client.sin_addr.s_addr = INADDR_ANY;
  bzero(&client.sin_zero, 0);

  len = sizeof(struct sockaddr_in);
  if ((connect(sock, (struct sockaddr *)&client, len)) == -1)
  {
    perror("connect: ");
    exit(-1);
  }
  int p, o, i, r;
  char w[100], t[100], y[100];

  printf("enrer city j :");
  scanf("%d", &q);
  cout << q << endl;
  int ans = 0;
  send(sock, &q, sizeof(q), 0);

  recv(sock, &ans, sizeof(ans), 0);
  recv(sock, &p, sizeof(p), 0);
  recv(sock, &w, sizeof(w), 0);
  recv(sock, &t, sizeof(t), 0);
  recv(sock, &y, sizeof(y), 0);
  recv(sock, &o, sizeof(o), 0);
  recv(sock, &i, sizeof(i), 0);
  recv(sock, &r, sizeof(r), 0);

  if (ans == 0)
    printf("Item is not available in store\n");
  else
  {
    cout << q << " " << ans << " " << p << " " << w << endl;
  }
  printf("%s\n", &w);

  close(sock);
  return 0;
}
