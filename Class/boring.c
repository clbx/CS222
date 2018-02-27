#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* new_strdup(char* source);

int main(){
  char string[1024];
  printf("Enter a String.");
  scanf("%s", string);

  char* duplicate = new_strdup(string);
  int size = strlen(string);
  int i;
  for(i = 0; i < size; ++i){
    if(string[i] >= 'A' && string[i] <= 'Z')
      string[i]+= 'a'-'A';
    else if(string[i] >= 'a' && string[i] <= 'z'){
      string[i] +='A' - 'a';
    }
  }
  printf("Original: %s", string);
  printf("Flipped: %s", duplicate);
  /*
  int value1, value2, value3;
  int count = 0;

  do{
    printf("Enter 3 integers: ");
    count = scanf("%d %d %d\n", &value1, &value2, &value3);
  }while(count != 3);
  printf("Value 1 %d, Value 2 %d, Value 3 %d.\n", value1, value2, value3);

  printf("were done!");
  */
  /*
  printf("Enter your name ");
  scanf("%s", name);
  printf("Enter your age ");
  scanf("%d", &age);
  printf("Hey, %s, your age doubled is %d\n", name, age*2);
  */
  return 0;
}

char* new_strdup(char* source){
  int size = 0;
  while(source[size] != '\0')
    size++;

  char* newString = (char*)malloc(sizeof(char)*(size+1));

  int i;
  for(i = 0; i <= size; ++i){
    newString[i] = source[i];
  }
  return newString;
}
