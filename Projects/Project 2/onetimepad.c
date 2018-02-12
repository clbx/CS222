/*******************************
*
*  Project Name: One Time, One Time
*  Description: A message encrypter and decrypter using an improved One Time Pad
*  File names: onetimepad.c, makefile, KEY.txt, MESSAGE.txt
*  Run Command: cat message1.txt delimiter.txt key1.txt | ./ontimepad
*  Date: 2/16/18
*  Authors: Clay Buxton (buxtonc@etown.edu), Lacie Flores (floresl@etown.edu)
*
*******************************/

#include <stdio.h>
#define MAX_STR 2048

void printstr(unsigned char str[], int length){
  int i;
  for(i = 0; i < length; i++){
    putchar(str[i]);
  }
}

void printints(unsigned char str[]){
  printf("Printing Ints \n");
  int i;
  for(i = 0; str[i] != 0; i++){
    printf("%d ", str[i]);
  }
}



int main(){
  unsigned char message[MAX_STR];  //The array our message will be stored in
  int messageLen = 0;              //How long the message is
  unsigned char key[MAX_STR];      //The array our key is stored in
  int keyLen = 0;

  //Try to do differently maybe? It's a little funky right now
  int inputChar = 0, i = 0;
  for(i = 0; (inputChar != 255) && (i < MAX_STR); i++){
    inputChar = getchar();
    if(inputChar != EOF && inputChar != 255){
      message[i] = inputChar;
      messageLen++;
    }
  }

  for(i = 0; (inputChar != EOF) && (keyLen < messageLen); i++){
    inputChar = getchar();
    if(inputChar != EOF && inputChar != 255){
      key[i] = inputChar;
      keyLen++;
    }
  }


  //Tiler
  if(keyLen < messageLen){
    int difference = messageLen - keyLen, i = 0;
    printf("Titling in Progress, key is %d char's shorter than message.\n", difference);
    for(i = 0; i < difference; i++){
      key[keyLen+i] = key[i];
      keyLen++;
    }

  }

  printf("\nPrinting the Message (Length: %d)\n\n", messageLen);
  printstr(message, messageLen);
  printf("\n\nPrinting the Key (Length: %d)\n\n", keyLen);
  printstr(key, keyLen);
  //Make sure the key is long enough if not:
    //Tile



  return 0;
}
