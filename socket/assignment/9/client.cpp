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
    char s[10000], ch[5] = "yes";
    int n, a = 1;
    char c;
    printf("Enter string : ");
    cin >> s;
    printf("Enter no : ");
    cin >> n;

    send(sock, &s, sizeof(s), 0);
    send(sock, &n, sizeof(n), 0);
    recv(sock, &a, sizeof(a), 0);
    recv(sock, &c, sizeof(c), 0);
    if (a == 1)
    {
      cout << n << " Frequency character is : " << c << endl;
    }
    else
    {
      cout << n << " Frequncy character not found !" << endl;
      cout << "Max frequency character is : " << c << endl;
    }
    printf("\ndo you want to exit...press 'yes' or 'no'\n");
    scanf("%s", ch);

    if ((strcmp(ch, "yes")) == 0)
    {
      close(sock);
      exit(0);
    }
  }

  return 0;
}