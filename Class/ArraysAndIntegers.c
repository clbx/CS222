#include <stdio.h>

int atoi(char* number);
char* itoa(int number, char* string);

int main(){

	return 0;
}


int atoi(char* number){
	int i = 0;
	int value = 0;
	int sign = 1;
	if(number[0] == '-'){
		sign = -1;
		i = 1;
	}
	while(number[i] != '\0'){
		value = value*10+number[i] - '0';
		i++;
	}
	value *= sign;

	return value;
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
	for(j = 0; i < i/2; j++){
		char temp = string[j];
		string[j] = string[i - j - 1];
		string[i - j - 1] = temp;
	}
}

