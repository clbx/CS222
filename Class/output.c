#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	printf("Give me an integer: ");
	int size;
	int n;
	scanf("%d", &size);
	char filename[100];
	printf("What is the name of the file you would like? ");
	scanf("%s", filename);
	FILE* file = fopen(filename, "wb");
	fprintf(file, "%d\n", size);

	fwrite(&n, sizeof(int), 1, file);
	srand(time(NULL));

	int i;
	for(i = 0; i < size; i++){
		//fprintf(file, "%d\n", rand());

	}
}
