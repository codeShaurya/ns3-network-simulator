/*
    $ g++ client.c -o client
    $./client
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int sock;
  int i, n = 0;
  unsigned int len;
  char q[100];
  char w[100];

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
  printf("enrer city");
  scanf("%s", &q);

  send(sock, &q, sizeof(q), 0);
  recv(sock, &n, sizeof(n), 0);
  recv(sock, &w, sizeof(w), 0);

  if (n == 0)
    printf("Item is not available in store\n");
  else
    printf("%s\n", &w);

  close(sock);
  return 0;
}
