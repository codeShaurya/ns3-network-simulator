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

/*
    $ g++ client.c -o client
    $./client
*/

int main(int argc, char *argv[])
{
  int sock;
  int i, n = -1;
  unsigned int len;
  int item_id = atoi(argv[3]);
  int q = atoi(argv[4]);

  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket: ");
    exit(-1);
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(atoi(argv[2]));
  client.sin_addr.s_addr = atoi(argv[1]);
  bzero(&client.sin_zero, 0);

  len = sizeof(struct sockaddr_in);
  if ((connect(sock, (struct sockaddr *)&client, len)) == -1)
  {
    perror("connect: ");
    exit(-1);
  }

  send(sock, &item_id, sizeof(item_id), 0);
  send(sock, &q, sizeof(q), 0);
  recv(sock, &n, sizeof(n), 0);

  if (n == -1)
    printf("Item is not available in store\n");
  else
    printf("Item has been purchased\n");

  close(sock);
  return 0;
}
