#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
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
  int a, i, j;
  int v[1000][1000];
  unsigned int len;
  char ch[3];

  struct sockaddr_in client;
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket:  ");
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
    printf("enter a numbers : ");
    scanf("%d", &a);
    send(sock, &a, sizeof(a), 0);
    recv(sock, &v, sizeof(v), 0);
    for (i = 0; i < a; i++)
    {
      for (j = 0; j < 2 * a - 1; j++)
      {
        printf("%c", v[i][j] ? '*' : ' ');
      }
      printf("\n");
    }

    printf("\ndo you want to exit ...press 'no'\n");
    scanf("%s", ch);
    if ((strcmp(ch, "yes")) == 0)
    {
      close(sock);
      exit(0);
    }
  }

  return 0;
}
