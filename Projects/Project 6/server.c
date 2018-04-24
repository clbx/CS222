/*
* Project Name: You got Served
* Description: Create a web server.
* File Names: server.c
* Project Due Date: 4/30/2018
* Authors: Kevin Carman and Clay Buxton
*/

//TODO/ASK: Favicon?
//TODO/ASK: Spaces in file names


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
	unsigned short port = 0;	//the port the server is listening on
	char* directory = NULL;		//the directory that the server is working out of
	int serverSocket = 0;		//holds the file desciptor for the server's socket
	int webSocket; 				//holds the file desciptor connection to web browser
	int value = 1;				//holds the option value for the socket
	struct sockaddr_in address;					//assigned name of server socket
	struct sockaddr_storage otherAddress;		//assigned name of web browser socket
	socklen_t otherSize = sizeof(otherAddress);	//holds the size of the web browser socket

	//returns if 3 arguments not supplied in the command line
	if(argc != 3){
		printf("Usage ./server <port> <path to root>\n");
		return -1;
	}

	//sets the port and directory
	port = atoi(argv[1]);
	directory = argv[2];

	//returns if directory can not be changed to
	if(chdir(directory) == -1){
		printf("Could not change to directory: %s\n", directory);
		return -1;
	}

	//get server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	//make it able to reuse ports
	setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));

	//bind socket to port and local IP
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = INADDR_ANY;

	//returns if port is invalid or in use
	if(bind(serverSocket, (struct sockaddr*)&address, sizeof(address)) != 0){
		printf("Bad port: %d\n", port);
		return -1;
	}

	//listen for a connection
	listen(serverSocket, 1);

	//setsockopt(webSocket, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value)); //not sure if needed to make websocket reusable

	while(1){
		//accept a connection
		webSocket = accept( serverSocket, (struct sockaddr *) &otherAddress, &otherSize);

		printf("Got a client:\n");

		//make sure connection is established
		/*
		if(webSocket == -1){
			printf("Could not establish connection on port %d\n", port);
			return -1;
		}
		*/

		char requestType[32];	//holds the request type
		char filePath[255];		//holds therequested file path
		char http[32];			//holds the http protocol
		char buffer[2048];		//buffer for receiving information
		char fileBuffer[2048];	//buffer for sending the file

		//receives information and stores in buffer
		recv(webSocket, buffer, sizeof(buffer) - 1, 0);

		//store the information received
		sscanf(buffer, "%s%s%s", requestType, filePath, http);
		printf("\t%s %s %s\n",requestType, filePath, http);

		int requestFlag = 0;	//flags if GET or HEAD request
		if(strcmp(requestType, "GET") == 0){
			requestFlag = 1;
		}
		if(strcmp(requestType, "HEAD") == 0){
			requestFlag = 2;
		}

		if(requestFlag){
			char* updatedFile = filePath;	//stores the updated file path

			//check if directory ends in a slash, concatenate index.html
			if(filePath[strlen(filePath)-1] == '/'){
				strcat(filePath, "index.html");
			}

			//check if directory is an absolute path, skip the slash
			if(filePath[0] == '/'){
				updatedFile++;
			}

			//execute GET or HEAD request
			if(requestFlag == 1){
				FILE* file = fopen(updatedFile, "rb");	//file to be sent

				if(file != NULL){
					//send the 200 OK reply for the header
					char* header = "HTTP/1.0 200 OK\r\n";
					send(webSocket, header, strlen(header), 0);

					//get information about the file to be sent
					struct stat fileInformation;			//struct for storing information about a given file
					stat(updatedFile, &fileInformation);	//retrieves information about the given file
					int fileSize = fileInformation.st_size;	//total size of file in bytes

					//send the content type for the header
					char contentType[1000];
					sprintf(contentType, "Content-Type: %s\r\n", typeCheck(updatedFile));
					send(webSocket, contentType, strlen(contentType), 0);

					//send the conetent length for the header
					char contentLength[1000];
					sprintf(contentLength, "Content-Length: %d\r\n\r\n", fileSize);
					send(webSocket, contentLength, strlen(contentLength), 0);

					//sends the file to the web browser
					int readBytes = 0;	//stores the number of bytes read from the file
					while((readBytes = fread(fileBuffer, sizeof(char), 2048, file)) != 0){
						send(webSocket, fileBuffer, readBytes, 0);
					}
					printf("Sent file: %s\n\n", updatedFile);
					fclose(file);

				}else{ //file == NULL
					printf("File not found: %s\n", updatedFile);
					//send the 404 reply for the header
					char* header = "HTTP/1.0 404 Not Found\r\n";
					send(webSocket, header, strlen(header), 0);

					//get information about the file
					struct stat fileInformation;			//struct for storing information about a given file
					stat("404.html", &fileInformation);		//retrieves information about the given file
					int fileSize = fileInformation.st_size;	//total size of file in bytes

					//send the content type for the header
					char contentType[1000];
					sprintf(contentType, "Content-Type: %s\r\n", typeCheck("404.html"));
					send(webSocket, contentType, strlen(contentType), 0);

					//send the content length for the header
					char contentLength[1000];
					sprintf(contentLength, "Content-Length: %d\r\n\r\n", fileSize);
					send(webSocket, contentLength, strlen(contentLength), 0);

					//sends the 404 file to the web browser
					file = fopen("404.html", "rb");	//file for 404 error
					int readBytes = 0;	//stores the number of bytes read from the file
					while((readBytes = fread(fileBuffer, sizeof(char), 2048, file)) != 0){
						send(webSocket, fileBuffer, readBytes, 0);
					}
					fclose(file);
				}
			}else{
				//send the 200 OK reply for the header
				char* header = "HTTP/1.0 200 OK\r\n";
				send(webSocket, header, strlen(header), 0);

				//get information about the file to be sent
				struct stat fileInformation;			//struct for storing information about a given file
				stat(updatedFile, &fileInformation);	//retrieves information about the given file
				int fileSize = fileInformation.st_size;	//total size of file in bytes

				//send the content type for the header
				char contentType[1000];
				sprintf(contentType, "Content-Type: %s\r\n", typeCheck(updatedFile));
				send(webSocket, contentType, strlen(contentType), 0);

				//send the content length for the header
				char contentLength[1000];
				sprintf(contentLength, "Content-Length: %d\r\n\r\n", fileSize);
				send(webSocket, contentLength, strlen(contentLength), 0);
				printf("Sent head: %s\n\n",updatedFile);
			}
		}
		close(webSocket);
	}
	close(serverSocket);
	return 0;
}

/*
	Name: typeCheck
	Description: Checks the type of the file requested based off of the extension.
	Parameters: updatedFile - the requested files name
	Returns: A string containing the type of file.
*/
char* typeCheck(char* updatedFile){
	char temp[25];	//string to hold the extension of the file
	int updatedFileLength = strlen(updatedFile);		//length of the updatedFile
	int i, j;

	//finds the index of the file extension starting from the end
	for(i = updatedFileLength; updatedFile[i - 1] != '.'; i--){}

	//stores the file extension in temp
	for(j = 0; updatedFile[i] != '\0'; j++){
		temp[j] = updatedFile[i];
		i++;
	}
	temp[j] = '\0';

	//determine/return the appropriate file type
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
