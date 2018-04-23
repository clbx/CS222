#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>


void readLine(char line[])
{
	int c = 0;
	int i = 0;

	while( (c = getchar()) != '\n' )
	{
		line[i] = c;
		i++;
	}

	line[i] = '\0';
}


int main(){
	int port;
	char ipAddress[50];
	char user[50];

	printf("Enter the port: ");
	scanf("%d", &port);
	printf("Enter IP Address: ");
	scanf("%s", ipAddress);
	printf("Enter your username: ");
	scanf("%s", user);

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress,
	& (address.sin_addr));

	connect(fd, (struct sockaddr *) &address, sizeof(address));
	getchar();
	char body[8192] = "";
	char message[8245] = "";
	while(strcmp(body, "stop") != 0){
		printf("Enter message to send: ");
		readLine(body);
		strcpy(message, user);
		strcat(message, ": ");
		strcat(message, body);
		send(fd, message, strlen(message)+1, 0);
	}
	close(fd);

}
