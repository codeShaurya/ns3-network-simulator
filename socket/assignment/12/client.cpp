/*
    $ g++ client.cpp -o client
    $ ./client
*/
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
  int sock;
  int i, n = 0;
  unsigned int len;

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

  while (1)
  {
    char s[1000], c[1000], v[10];
    printf("Enter question :\n");
    scanf("%[^\n]", s);

    send(sock, &s, sizeof(s), 0);
    recv(sock, &c, sizeof(c), 0);
    printf("Answer = %s\n", c);

    printf("Do you want to continue... press 'yes' or 'no' ");
    scanf("%s", v);
    if (strcmp(v, "no") == 0)
      break;
  }

  close(sock);
  return 0;
}
