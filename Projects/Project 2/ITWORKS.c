/*******************************
*
*  Project Name: One Time, One Time
*  Description: A message encrypter and decrypter using an improved One Time Pad
*  File names: onetimepad.c, makefile, keyX.txt, messageX.txt
*  Run Command: cat messageX.txt delimiter.txt keyX.txt | ./ontimepad
*  Date: 2/16/18
*  Authors: Clay Buxton (buxtonc@etown.edu), Lacie Flores (floresl@etown.edu)
*
*******************************/

#include <stdio.h>
#define MAX_STR 2048

//Define our functions
void printstr(unsigned char str[], int length);
void printints(unsigned char str[]);
int rotate(unsigned char character, int count);
int bits(unsigned char inputChar);



int main(){
  unsigned char message[MAX_STR];  //The array our message will be stored in
  int messageLen = 0;              //How long the message is
  unsigned char key[MAX_STR];      //The array our key is stored in
  int keyLen = 0;

  //Try to do differently maybe? It's a little funky right now
  int inputChar = 0, i = 0, flag = 1;
  for(i = 0; (inputChar != 255) && (i < MAX_STR); i++){
    inputChar = getchar();
    if(inputChar != EOF && inputChar != 255){
      message[i] = inputChar;
      messageLen++;
    }
    else if(inputChar == 255)
      flag = 0;
  }
  if(flag){
    int shit;
    while(shit != 255){
      shit = getchar();
    }
  }

  for(i = 0; (inputChar != EOF) && (keyLen < messageLen); i++){
    inputChar = getchar();
    if(inputChar != EOF && inputChar != 255){
      key[i] = inputChar;
      keyLen++;
    }
  }
  //printf("\nPrinting the Message (Length: %d)\n\n", messageLen);
  //printstr(message, messageLen);


  //Tiler
  if(keyLen < messageLen){
    int difference = messageLen - keyLen, i = 0;
    //printf("\n\nTiling in Progress, key is %d char's shorter than message.\n", difference);
    for(i = 0; i < difference; i++){
      key[keyLen+i] = key[i];
    }
    keyLen = messageLen;

  }
  /*
  printf("\n\nPrinting the Key (Length: %d)\n\n", keyLen);
  printstr(key, keyLen);
  printf("\n");
  */

  //Encrypt key
  int sum = key[keyLen-1]%keyLen;
  //printf("Sum: %c", sum);
  //unsigned char chainedKey[keyLen];
  int bitOp = keyLen-1;
  for(i = 0; i < keyLen; i++){
    key[i] = rotate((key[i]^key[sum]),bits(key[bitOp]));
    sum+=key[i];
    sum = sum % keyLen;
    bitOp = i;
  }




/*
  int test = rotate('5',2);
  printf("%d\n", test);
  int testbits = bits(7);
  printf("%d\n", testbits);
  printf("\n\nEncrypted Key\n");
  printstr(key, keyLen);
  printf("\n\nEnd Sum: %c", sum);
*/

  //Make sure the key is long enough if not:
    //Tile
unsigned char outputMessage[keyLen];
for(i = 0; i < keyLen; i++){
  outputMessage[i] = key[i] ^ message[i];
}

//printf("\n\nOUTPUT MESSAGE:\n");
printstr(outputMessage, keyLen);

return 0;
}


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

int rotate(unsigned char character, int count){
	return (127 & ((character >> count) | (character <<(7 - count))));

}

int bits(unsigned char inputChar){
  int totalBits = 0;
  while(inputChar){
    totalBits += inputChar & 1;
    inputChar >>= 1;
  }
  return totalBits;
}
