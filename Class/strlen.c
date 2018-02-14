#include <stdio.h>

int getLength(char string[]){
  int i;
  for(i = 1; string[i] != '\0'; i++)
    ;
  return i;
}

void reverse(char string[], int length){
  int i = 0;
  int strlen = getLength(string);
  for(i = 0; i < strlen/2; i++){
    char temp = string[i];
    string[i] = string[strlen - 1 - i];
    string[strlen - 1 - i] = temp;

  }
}


int main(){
  char text[] = "yeet";
  int size = getLength(text);
  printf("The lengthof \"%s\" is %d.\n", text, size);
  reverse(text, size);
  printf("%s", text);
}
