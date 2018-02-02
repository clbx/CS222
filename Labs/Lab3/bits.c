#include <stdio.h>

int readInt(){
	int c = 0;
	int i = 0;

	while( (c = getchar()) != EOF && c != '\n' ){
		if( c >= '0' && c <= '9')
			i = i * 10 + (c - '0');
    else if((c = '\n')){
    }
	}
	return i;
}


int main(){
	int value = 0;
  int func;
  int bitflip = 1;
  int origvalue;
  int shiftby = 0;
	printf("Enter an integer: ");
	value = readInt();
  origvalue = value;
  printf("Do you want to set, unset, or flip a bit? (s, u, f): ");
  func = getchar();
  printf("Which bit? (0-31): ");
  readInt();
  shiftby = readInt();


  bitflip = bitflip << shiftby;
  //printf("Currently editing the %d's digit\n", bitflip);

  switch(func){
    case('s'):
      value = value | bitflip;
      printf("The result of setting bit %d in %d is %d\n", shiftby,origvalue,value);
      break;
    case('u'):
      value = (value & ~bitflip);
      printf("The result of unsetting bit %d in %d is %d\n", shiftby,origvalue,value);
      break;
    case('f'):
      value = value ^ bitflip;
      printf("The result of flipping bit %d in %d is %d\n", shiftby,origvalue,value);
      break;
    default:
      printf("Learn to read\n");
      break;
  }



	return 0;
}
