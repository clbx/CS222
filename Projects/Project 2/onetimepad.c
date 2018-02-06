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

char input[MAX_STR];                                          //Declaring a "string" for our input message
char key[MAX_STR];                                            //Delcaring a "string" for our key

/*
int rotate(){

}*/




int getstr(){
  int c, i = 0;
  //(char)255
  while((c=getchar()) != EOF){
    input[i] = c;
    i++;
  }
  printf("Finished\n");
  /*
  i = 0;
  c = getchar();
  putchar(c);
  putchar('*');
  printf("WE GET HERE\n");
  while(c != EOF){
    c = getchar();
    key[i] = c;
    putchar(c);
    i++;
  }*/

  return 0;
}


int main(){
  getstr();

  printf("%s", input);
  //printf("Finished first loop");
  //printf("%s", key);
  //Get the message
  //Get the key
  //Make sure the key is long enough if not:
    //Tile




  return 0;
}
