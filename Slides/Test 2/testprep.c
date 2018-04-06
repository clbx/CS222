#include<stdio.h>

char* itoa(int number, char* string);

int main(){
  
  char* string[100];
  int number = -5682;

  printf("%s\n", itoa(number, *string));
}


char* itoa(int number, char* string){
	int negative = 0;
	if(number < 0){
		number *=-1;
		negative = 1;
	}


	int i = 0;
	while(number != 0){
		int digit = number%10;
		number = number/10;
		string[i] = digit + '0';
		i++;
	}
	if(negative){
		string[i] = '-';
		i++;
	}

	string[i] = '\0';
	int j = 0;
	for(j = 0; j < i/2; j++){
		char temp = string[j];
		string[j] = string[i - j - 1];
		string[i - j - 1] = temp;
	}

  return string;
}
