#include <stdio.h>
#include <stdio.h>



int main(){
	printf("What file do you want to open\n");
	char filename[100];
	scanf("%s", filename);

	FILE* file= fopen(filename, "r");
	int total;
	fscanf(file,"%d", &total);


	int* array = (int*)malloc(sizeof(int)*n);

	int i;
	int number;
	int sum = 0;
	for(i = 0; i < total; i++){
		fscanf(file, "%d", &number);
		sum = sum + number;
	}

	double average = sum / 2;
	printf("The average is:%f\n", average);
}
