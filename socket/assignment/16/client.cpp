/*
    $ g++ client.cpp -o client
    $ ./client
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

int main()
{
  int sock;
  unsigned int len;
  char s[100];
  char t[100];

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

  printf("Enter password\n");
  scanf("%s", s);
  send(sock, &s, sizeof(s), 0);
  recv(sock, &t, sizeof(t), 0);
  cout << t << endl;

  close(sock);
  return 0;
}
