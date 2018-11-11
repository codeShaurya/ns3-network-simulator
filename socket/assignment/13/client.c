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

void main()
{
	int sock;
	unsigned int len;
	char s[100];
	char c[1000];
	FILE *f;
	char x;
	int i;

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

	printf("Enter file name\n");
	scanf("%s", s);
	send(sock, &s, sizeof(s), 0);
	recv(sock, &c, sizeof(c), 0);
	f = fopen("abc.txt", "wb");
	i = 0;
	while (c[i] != '\0')
		fprintf(f, "%c", c[i++]);

	close(sock);
}
