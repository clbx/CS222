#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main( int argc, char **argv )
{
	unsigned short port = 0;
	int serverSocket = 0;
	int clientSocket = 0;
	char buffer[1024];
	int length = 0;
	int value = 1;
	struct sockaddr_in address;
	struct sockaddr_storage otherAddress;
	socklen_t otherSize = sizeof(otherAddress);

	//read port from user
	printf("Enter port: ");
	scanf("%hd", &port);

	//get socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//make it able to reuse ports
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	//bind socket to port and local IP
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;
	bind(serverSocket, (struct sockaddr*)&address, sizeof(address));

	//listen
	listen(serverSocket, 1);

	//accept
	clientSocket = accept( serverSocket, (struct sockaddr *) &otherAddress, &otherSize);

	printf("\n\n*Chat Started*\n");

	//receive messages
	while( (length = recv( clientSocket, buffer, sizeof(buffer) - 1, 0)) > 0 )
	{
		buffer[length] = '\0';

		if( strcmp( buffer, "quit" ) == 0 )
			break;

		printf("%s\n", buffer);
	}

	printf("\n*Chat Ended*\n");

	//clean up
	close( clientSocket );
	close( serverSocket );

	return 0;
}
