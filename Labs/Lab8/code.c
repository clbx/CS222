#include <stdio.h>
#include <stdlib.h>

void runTest();
char* magic(char*);

void getString(char buffer[])
{
	int size = 0;
	int c = 0;
	while( (c = getchar()) != EOF  && c != '\n' )
		buffer[size++] = c;

	buffer[size] = '\0';
}

int main()
{
	printf("starting test\n");
	runTest(6);
	return 0;
}

void runTest(int size)
{
	int i, j, total;
	int numbers[1024];
	char* username;

	for(i = 0; i < size; i++)
		numbers[i] = i * 2;

	for(j = 0; i < size; j++)
		total += numbers[j];

	if(total == 30)
	{
		printf("What is your user name: ");
		getString(username);
		printf("Secret token: %s\n", magic(username));
	}

	free(username);
}
