/*
* Project Name: You got Served
* Description: Create a web server.
* File Names: server.c
* Project Due Date: 4/30/2018
* Authors: Kevin Carman and Clay Buxton
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>

char* typeCheck(char* directory);

int main( int argc, char **argv ){

	unsigned short port = 0;
	int serverSocket = 0;
	int value = 1;
	struct sockaddr_in address;
	struct sockaddr_storage otherAddress;
	socklen_t otherSize = sizeof(otherAddress);


	if(argc != 3){
		printf("Usage ./server <port> <path to root>\n");
		return -1;
	}

	port = atoi(argv[1]);
	char* directory = argv[2];

	if(chdir(directory) == -1){
		printf("Could not change to directory: %s\n", directory);
		return -1;
	}

	//get socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//make it able to reuse ports
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	//bind socket to port and local IP
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	//if port is invalid or in use, will return -1
	if(bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) != 0){
		printf("Bad port: %d\n", port);
		return -1;
	}

	//listen for a connection
	listen(serverSocket, 1);

	int webSocket; //file desciptor connection to web browser

	//not sure if needed to make websocket reusable
	//setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));



	//do we need an exit condition?
	while(1){
		//Accept a connection
		webSocket = accept( serverSocket, (struct sockaddr *) &otherAddress, &otherSize);

		printf("Connection established.\n");
		//make sure connection is established

		if(webSocket == -1){
			printf("Could not establish connection on port %d\n", port);
			return -1;
		}

		//receive information
		/*
		if(recv( webSocket, buffer, sizeof(buffer) - 1, 0) == -1){
			printf("Could not receive information.\n");
			return -1;
		}
		*/

		char requestType[4];
		char filePath[255];
		char http[8];
		char buffer[1024];
		char fileBuffer[2048];
		int pathLength = 0;

		recv(webSocket, buffer, sizeof(buffer) - 1, 0);

		for(int i = 0; i < 254; i++){
			filePath[i] = ' ';
		}
		filePath[255] = '\0';

		sscanf(buffer, "%s %s %s", requestType, filePath, http);

		while(filePath[pathLength] != ' '){
			pathLength++;
		}

		int requestFlag = 0;	//flags if GET or HEAD request
		if(strncmp(requestType, "GET", 3) == 0){
			requestFlag = 1;
		}
		if(strncmp(requestType, "HEAD", 4) == 0){
			requestFlag = 2;
		}

		if(requestFlag){

			//check if directory ends in a slash, concatenate index.html

			if(directory[strlen(directory)-1] == '/'){
				strcat(directory, "index.html");
			}



			//check if directory is an absolute path, skip the slash
			/*
			if(directory[0] == '/'){
				int i;
				for(i = 1; i < strlen(directory); i++){
					directory[i - 1] = directory[i];
				}
				directory[i] = '\0';
			}
			*/
			printf("%s\n", directory);


			//execute GET or HEAD request
			if(requestFlag == 1){
				printf("GET Request\n");
				FILE* file = fopen(directory, "rb");
				if(file != NULL){

					printf("In file Dir: %s\n", directory);
					printf("In file Typecheck: %s\n", typeCheck(directory));

					char* header;
					header = "HTTP/1.0 200 OK\r\n";
					//sprintf(header, "%s 200 OK\r\n", http);
					send(webSocket, header, strlen(header), 0);

					struct stat fileInformation;	//struct for storing information about a given file
					stat(filePath, &fileInformation);	//retrieves information about the given file
					int fileSize = fileInformation.st_size;	//total size of file in bytes

					printf("before typecheck");
					char* contentType;
					contentType = " ";
					sprintf(contentType, "Content-Type: %s\r\n", typeCheck(directory));
					printf("after typecheck\n");
					send(webSocket, contentType, strlen(contentType), 0);
					printf("Gets to Type\n");


					char* contentLength;
					contentLength = " ";
					sprintf(contentLength, "Content-Length: %d\r\n\r\n", fileSize);
					send(webSocket, contentLength, strlen(contentLength), 0);
					printf("Gets to Len\n");


					int readBytes = 0;
					while((readBytes = fread(fileBuffer, sizeof(char), 2048, file)) != 0){
						send(webSocket, fileBuffer, readBytes, 0);
					}
					printf("GET request successful.\n");
				}else{ //file == NULL
					printf("file invalid\n");
				}
			}
		}
		break;
		close(webSocket);
	}

	close(serverSocket);
	return 0;
}

char* typeCheck(char* directory){
	char temp[25];
	int directoryLength = strlen(directory);
	int i, j;

	//finds the index of the file extension starting from the end
	for(i = directoryLength; directory[i - 1] != '.'; i--){}

	//stores the file extension in temp
	for(j = 0; directory[i] != '\0'; j++){
		temp[j] = directory[i];
		i++;
	}
	temp[j] = '\0';
	printf("%s", temp);
	printf("Here4\n");

	//determine the file type
	if(strcmp(temp, "html") == 0){
		return "text/html";
	}else if(strcmp(temp, "htm") == 0){
		return "text/html";
	}else if(strcmp(temp, "jpg") == 0){
		return "image/jpeg";
	}else if(strcmp(temp, "jpeg") == 0){
		return "image/jpeg";
	}else if(strcmp(temp, "gif") == 0){
		return "image/gif";
	}else if(strcmp(temp, "png") == 0){
		return "image/png";
	}else if(strcmp(temp, "txt") == 0){
		return "text/plain";
	}else if(strcmp(temp, "c") == 0){
		return "text/plain";
	}else if(strcmp(temp, "h") == 0){
		return "text/plain";
	}else if(strcmp(temp, "pdf") == 0){
		return "application/pdf";
	}else{
		return "application/unknown";
	}
}

/*
/r/n then double /r/n after header
SO_REUSEADDR otherwise if you crash and reconnect to a socket it will wait a minute //4/16

1024-65656
set socket before listening to it
*/

/*
Enter port: 5000
!!Connection Received

GET / HTTP/1.1
Host: 127.0.0.1:5000
User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:59.0) Gecko/20100101 Firefox/59.0
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,**;q=0.8
Accept-Language: en-US,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Upgrade-Insecure-Requests: 1
Cache-Control: max-age=0
*/
