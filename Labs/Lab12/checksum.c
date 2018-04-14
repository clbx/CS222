#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){

	if(argc < 2 || argc > 2 || argv[1][0] == '-'){
		printf("Usage: ./checksum <filename>\n");
		return 0;
	}

	int fd = open(argv[1], O_RDONLY);

	if(fd < 0){
		printf("%s: No such file or directory\n", argv[1]);
		return 0;
	}

	int bytes = 1;
	int totalbytes = 0;
	unsigned int sum = 0;
	unsigned char buffer;

	while(bytes == 1){
		bytes = read(fd, &buffer, sizeof(char));
		if(bytes){
			sum += buffer;
			totalbytes++;
		}
	}
	unsigned int r, s;
	r = (sum % (2<<15)) + (sum / (2 << 15));
	s = (r % (2 << 15)) + (r / (2 << 15));

	//printf("%d", s);

	int blocks = totalbytes/512;

	if(totalbytes % 512 != 0){
		blocks++;
	}

	printf("%d %d %s\n", s, blocks, argv[1]);


	close(fd);

	return 0;
}
