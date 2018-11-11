
/*
  $	g++ client.cpp -o client
	$ ./client
*/

#include <bits/stdc++.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
int main()
{
	int sock;
	unsigned int len;
	char s[100];
	FILE *f;
	char x;
	int i, n = 0;

	struct sockaddr_in client;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket: ");
		exit(-1);
	}

	client.sin_family = AF_INET;
	client.sin_port = htons(10009);
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
		cout << "Press 0 to receive message, 1 to send message";
		int c;
		cin >> c;
		send(sock, &c, sizeof(c), 0);
		if (c == 0)
		{
			int number;
			recv(sock, &number, sizeof(number), 0);
			cout << number << endl;
			for (int i = 0; i < number; ++i)
			{
				char buffer[1024];
				recv(sock, buffer, 1024, 0);
				cout << buffer << endl;
			}
		}
		else
		{
			char buffer[1024];
			cin >> buffer;
			send(sock, buffer, 1024, 0);
		}
	}
}
