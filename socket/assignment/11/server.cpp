/*
    $ g++ server.cpp -o server
    $ ./server
*/
#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

struct dic
{
  char w[100];
  char m[100];
};

int main()
{
  struct dic D[100];
  struct sockaddr_in server, client;
  int ssock, csock;
  unsigned int length = sizeof(struct sockaddr_in);

  strcpy(D[0].w, "pen");
  strcpy(D[0].m, "is used to write");

  strcpy(D[1].w, "pencil");
  strcpy(D[1].m, "is aloso used to write");

  strcpy(D[2].w, "eraser");
  strcpy(D[2].m, "is used to erase");

  strcpy(D[3].w, "laptop");
  strcpy(D[3].m, "is a electornioc device");

  strcpy(D[4].w, "mobile");
  strcpy(D[4].m, "is used to talk");

  if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket failed");
    exit(-1);
  }

  server.sin_family = AF_INET;
  server.sin_port = htons(10001);
  server.sin_addr.s_addr = INADDR_ANY;
  bzero(&server.sin_zero, 0);

  if ((bind(ssock, (struct sockaddr *)&server, length)) == -1)
  {
    perror("bind failed");
    exit(-1);
  }

  if ((listen(ssock, 5)) == -1)
  {
    perror("server is not listening");
    exit(-1);
  }

  if ((csock = accept(ssock, (struct sockaddr *)&client, &length)) == -1)
  {
    perror("falied");
    exit(-1);
  }

  while (1)
  {
    char w[100];
    int total_count = 4;
    int index = -1;
    char d[10] = "not_found";

    recv(csock, &w, sizeof(w), 0);
    cout << "client wants to know : " << w << endl;

    for (int i = 0; i < total_count; i++)
    {
      if (strcmp(D[i].w, w) == 0)
      {
        index = i;
        break;
      }
    }

    if (index == -1)
    {
      cout << "word not found" << endl;
      strcpy(D[++total_count].w, w);
      strcpy(D[++total_count].m, "server is searching on the internet");
      send(csock, &d, sizeof(d), 0);
    }
    else
    {
      cout << "sent meaning : " << D[index].m << endl;
      send(csock, &D[index].m, sizeof(D[index].m), 0);
    }
  }

  close(ssock);
  return 0;
}