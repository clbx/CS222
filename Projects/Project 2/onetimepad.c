/*******************************
*
*  Project Name: One Time, One Time
*  Description: A message encrypter and decrypter using an improved One Time Pad
*  File names: onetimepad.c, makefile, KEY.txt, MESSAGE.txt
*  Date: 2/16/18
*  Authors: Clay Buxton (buxtonc@etown.edu), Lacie Flores (floresl@etown.edu)
*
*******************************/

#include <stdio.h>
#define MAX_STR 2048

void printstr(char str[]){
  printf("Printing String");
  int i;
  for(i = 0; str[i] != 0; i++){
    putchar(str[i]);
  }
}



int main(){
  char input[MAX_STR];
  char key[MAX_STR];
  int c, i = 0;
  for(i = 0; i != 255 && i != EOF; i++){
    c = getchar();
    input[i] = c;
  }

  printstr(input);
  //printf("%s", key);
  //Get the message
  //Get the key
  //Make sure the key is long enough if not:
    //Tile




  return 0;
}
