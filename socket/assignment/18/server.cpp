/*
  $	g++ server.cpp -pthread -o server
	$ ./server
*/

#include <bits/stdc++.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

using namespace std;
vector<char *> buffers;
void *connection(void *c)
{
	int csock = *((int *)c);
	while (1)
	{
		int status;
		recv(csock, &status, sizeof(status), 0);
		if (status == 0)
		{
			int s = buffers.size();
			cout << s << endl;
			send(csock, &s, sizeof(s), 0);
			for (int i = 0; i < s; ++i)
			{
				send(csock, buffers[i], 1024, 0);
			}
		}
		else if (status == 1)
		{
			char newBuffer[1024];
			recv(csock, newBuffer, 1024, 0);
			buffers.push_back(newBuffer);
		}
	}
}
int main()
{
	int ssock, csock;
	sockaddr_in server, client;
	if ((ssock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket:");
		exit(-1);
	}
	unsigned int len;
	server.sin_port = htons(10009);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(server.sin_zero, 0);
	len = sizeof(server);
	if (bind(ssock, (sockaddr *)&server, len) == -1)
	{
		perror("connect failed:");
		exit(-1);
	}

	vector<pthread_t> threads;

	while (1)
	{
		if (listen(ssock, 5) == -1)
		{
			perror("Listening failed");
			exit(-1);
		}
		if ((csock = accept(ssock, (sockaddr *)&client, &len)) == -1)
		{
			perror("Accepting failed");
			exit(-1);
		}
		pthread_t newThread;
		threads.push_back(newThread);
		pthread_create(&threads.back(), NULL, connection, (void *)&csock);
		// char pro[100];
		// recv(csock, &pro,sizeof(pro),0);
		// int quantity;
		// recv(csock, &quantity,sizeof(quantity),0);
		// int status =0,price;
		// for(int i=0;i<n;i++){
		// 	if(strcmp(pro,product_name[i])==0){
		// 		if(quantity<remaining[i]){
		// 			status=1;
		// 			price = quantity* product_price[i];
		// 		}
		// 	}
		// }
		// send(csock,&status,sizeof(status),0);
		// if(status==1){
		// 	send(csock,&price,sizeof(price),0);
		// }
	}
}