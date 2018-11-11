#include <bits/stdc++.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
using namespace std;
#define N strlen(g)
char t[28], cs[28], g[] = "10001000000100001";
int a, e, c;

void xors()
{
	for (c = 1; c < N; c++)
		cs[c] = ((cs[c] == g[c]) ? '0' : '1');
}

void crc()
{
	for (e = 0; e < N; e++)
		cs[e] = t[e];
	do
	{
		if (cs[0] == '1')
			xors();
		for (c = 0; c < N - 1; c++)
			cs[c] = cs[c + 1];
		cs[c] = t[e++];
	} while (e <= a + N - 1);
}

int main()
{
	int ssock, csock;
	sockaddr_in server, client;
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket:");
		exit(-1);
	}
	server.sin_port = htons(10000);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 0);
	unsigned int length = sizeof(server);
	if (bind(ssock, (sockaddr *)&server, length) == -1)
	{
		perror("bind:");
		exit(-1);
	}
	if (listen(ssock, 5) == -1)
	{
		perror("listen:");
		exit(-1);
	}
	if ((csock = accept(ssock, (sockaddr *)&client, &length)) == -1)
	{
		perror("listen:");
		exit(-1);
	}
	while (1)
	{
		int size = 100;
		int a;
		recv(csock, &a, sizeof(a), 0);
		recv(csock, t, (a), 0);
		recv(csock, &a, sizeof(a), 0);
		recv(csock, cs, (a), 0);
		crc();
		for (e = 0; (e < N - 1) && (cs[e] != '1'); e++)
			;
		if (e < N - 1)
			printf("\nError detected\n\n");
		else
			printf("\nNo error detected\n\n");
		printf("\n----------------------------------------\n");
	}
}
