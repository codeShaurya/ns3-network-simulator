/*
  Command line arguement :
        1. port number
  Ex.
  $ ./a.out 10000
*/
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

int main(int argc, char *argv[])
{
  int ssock, csock;
  unsigned int length = sizeof(struct sockaddr_in);
  struct sockaddr_in client, server;

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket creation falied");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[1]));
  server.sin_addr.s_addr = INADDR_ANY;

  bzero(&server.sin_zero, 0);

  if ((bind(ssock, (struct sockaddr *)&server, length)) == -1)
  {
    perror("bind failed");
    exit(-1);
  }

  if (listen(ssock, 5) == -1)
  {
    perror("listen failed");
    exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &length)) == -1)
  {
    perror("bind failed");
    exit(-1);
  }

  char buffer[1000];
  char filename[100];
  FILE *f;
  int c;

  recv(csock, &filename, sizeof(filename), 0);
  recv(csock, &buffer, sizeof(buffer), 0);

  f = fopen(filename, "w");
  fprintf(f, "%s", buffer);

  cout << buffer << endl;
  cout << filename << endl;

  if (f == NULL)
  {
    c = -1;
    cout << "File upload failed \n";
    exit(-1);
  }
  else
  {
    c = 1;
    printf("\nthe file was received successfully\n");
    cout << "the new file uoploaded as :" << filename << endl;
  }

  send(csock, &c, sizeof(c), 0);

  return 0;
}