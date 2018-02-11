#include <stdio.h>

/**
 * Function: 	readInt
 * Returns: 	an int, read from standard input.
 **/
int readInt()
{
	int c = 0;
	int i = 0;
	while( (c = getchar()) != EOF && c != '\n' ){
		if( c >= '0' && c <= '9')
			i = i * 10 + (c - '0');
	}
	return i;
}
/**
 * Function: 	getFactorial
 * Returns: 	the factorial of an entered integer.
 **/
long long getFactorial(int input){
  if(input >= 1)
    return input * getFactorial(input -1);
  else
    return 1;
}

int main(){

  int lines;
  printf("Enter an Integer: ");    //Get input
  lines = readInt();
  if(lines > 20){
    printf("Invalid Input\n");    //Sanatize that input
    return 0;
  }

  int i=0, j=0;
  long long pascalNumber;

  for(i = 0; i <= lines; i++){     //As many lines as entered
    for(j=0; j <= i; j++){         //The line number is also how many columns there are
      //printf("(%d, %d)", i, j);
      pascalNumber = (getFactorial(i))/((getFactorial(i-j))*(getFactorial(j)));   //The Equation
      printf("%lld ", pascalNumber); //Let the world know
    }
    printf("\n");                     //Give each line a personal bubble
  }





  return 0;
}
