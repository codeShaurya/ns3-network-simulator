#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

/*
    $ g++ client.c -o client
    $ ./client
*/

int main()
{
  int sock;
  int a, i = 0;
  int v[100];
  unsigned int len;
  char c;
  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("error");
    exit(-1);
  }

  for (i = 0; i < 100; i++)
    v[i] = -1;

  client.sin_family = AF_INET;
  client.sin_port = htons(10000);
  client.sin_addr.s_addr = INADDR_ANY;
  bzero(&client.sin_zero, 0);

  len = sizeof(struct sockaddr_in);
  if ((connect(sock, (struct sockaddr *)&client, len)) == -1)
  {
    perror("error");
    exit(-1);
  }

  while (1)
  {
    printf("enter a number\n");
    scanf("%d", &a);
    send(sock, &a, sizeof(a), 0);
    recv(sock, v, sizeof(v), 0);
    for (i = 0; i < 100; i++)
    {
      if (v[i] == -1)
        break;
      printf("%d ", v[i]);
    }

    printf("\npress N to exit\n");
    scanf("%c", &c);
    if (c == 'N')
    {
      close(sock);
      exit(0);
      break;
    }
  }

  return 0;
}