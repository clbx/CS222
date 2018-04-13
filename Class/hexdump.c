#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>


int main(){
	printf("What file do you want to open? ");
	char filename[256];
	scanf("%s", filename);

	int fd = open(filename, O_RDONLY);

	char buffer[16];
	read(fd, buffer, sizeof(char)*16);

	int bytes = 16;

	while(bytes == 16){
		read(fd, buffer, sizeof(char)*16);

	}


	close(fd);

	return 0;
}
