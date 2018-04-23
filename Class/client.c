#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

void realine( buffer[] m){
	int i = 0;
	char c;
	while( (c=getchar()) != '\0'){

	}

}


int main(){




	printf("What is the port ");
	int port;
	scanf("%d", &port);

	char ipAddress[50];
	printf("Enter IP address ");
	scanf("%s", ipAddress);

	int fd = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress,
	& (address.sin_addr));

	connect(fd, (struct sockaddr *) &address, sizeof(address));

	char message[8192] = "";
	while(strcmp(message, "stop") != 0){
		printf("Enter the message you would like to send: ");
		scanf("%s", message);
		send(fd, message, strlen(message)+1, 0);
	}
	close(fd);

}
