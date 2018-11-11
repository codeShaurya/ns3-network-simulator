#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

/*
  Command line arguement :
        1. INADDR_ANY
        2. port
        3. get
        4. filename
  Ex.
  $ ./a.out INADDR_ANY 10000 get file.txt
*/

int main(int argc, char *argv[])
{
  int sock;
  unsigned int length = sizeof(struct sockaddr_in);
  struct sockaddr_in client;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket failed");
    exit(-1);
  }
  client.sin_family = AF_INET;
  client.sin_port = htons(atoi(argv[2]));
  client.sin_addr.s_addr = atoi(argv[1]);

  bzero(&client.sin_zero, 0);

  if ((connect(sock, (struct sockaddr *)&client, length)) == -1)
  {
    perror("connection falied");
    exit(-1);
  }

  char buffer[1000];
  FILE *f;
  int c, n;

  send(sock, argv[4], sizeof(argv[4]), 0);

  recv(sock, &buffer, sizeof(buffer), 0);
  f = fopen(argv[4], "w");
  fprintf(f, "%s", buffer);

  recv(sock, &c, sizeof(c), 0);

  if (c == 1)
    cout << " File downloaded successfully" << endl;
  else
    cout << "file downloading failed :" << endl;

  return 0;
}