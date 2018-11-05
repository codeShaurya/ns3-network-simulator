#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

int main()
{
  int sock;
  unsigned int length = sizeof(struct sockaddr_in);
  struct sockaddr_in client;

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Socket connection failed");
    exit(-1);
  }
  else
  {
    cout << "socket created" << endl;
  }

  client.sin_family = AF_INET;
  client.sin_port = htons(10001);
  client.sin_addr.s_addr = INADDR_ANY;

  bzero(&client.sin_zero, 0);

  if ((connect(sock, (struct sockaddr *)&client, length)) == -1)
  {
    perror("Connection failed");
    exit(-1);
  }
  else
  {
    cout << "connected successfully" << endl;
  }

  while (1)
  {
    string n;
    char s[100], w[100];
    cout << "Enter a string : ";
    cin >> s;

    send(sock, &s, sizeof(s), 0);
    recv(sock, &w, sizeof(w), 0);

    cout << "server returns : ";
    if (strcmp(w, "not_found") == 0)
    {
      cout << "word Not found in dictionary" << endl;
      cout << "server is adding the word in the dictionary" << endl;
    }
    else
      cout << s << " means " << w << endl;

    cout << "Do you want to continue .....";
    cin >> n;
    if (n != "yes")
      break;
  }

  close(sock);
  return 0;
}