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
#define MAX_STR 2048                                                            //This is the max size a "string" can be per instructions
                                                                                         //Define our functions.
void printstr(unsigned char str[], int length);                                          //This will print an array of characters.
void printints(unsigned char str[]);                                                     //This will print an array of characters w/ interger values. Was used for input debugging.
int getLength(unsigned char str[]);                                                      //This will output the length of said array, originally used for debugging but came in handy later.
int rotate(unsigned char character, int count);                                          //This will rotate all but the most signifigant bit in a value.
int bits(unsigned char inputChar);                                                       //This will output how many 1's are in the binary representation of a value.
void getInputs(unsigned char message[], unsigned char key[], int messageLen, int keyLen);//This will get the inputs from the user and put them into the character arrays.
void tiler(unsigned char key[], int messageLen, int keyLen);                             //This will ensure the key is as long as the message by repeating it until it is.
void chainer(unsigned char message[], unsigned char key[], int keyLen, int messageLen);  //This will run the chaining function to help strengthen the key encryption.
void encrypt(unsigned char message[], unsigned char key[], int keyLen);                  //This will XOR each character in key and message against each other completing the encryption.

int main(){

  unsigned char message[MAX_STR];
  int messageLen = 0;                                                           //How long the message is
  unsigned char key[MAX_STR];                                                   //The array our key is stored in
  int keyLen = 0;
  getInputs(message, key, messageLen, keyLen);
  if(keyLen < messageLen){
    tiler(key, messageLen, keyLen);
  }
  chainer(message, key, keyLen, messageLen);
  encrypt(message, key, keyLen);
  printstr(message, keyLen);
  return 0;
}



void getInputs(unsigned char message[], unsigned char key[], int messageLen, int keyLen){
  int inputChar = 0, flag = 1, i = 0;
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
}

void tiler(unsigned char key[], int messageLen, int keyLen){
  int difference = messageLen - keyLen, i = 0;
  //printf("\n\nTiling in Progress, key is %d char's shorter than message.\n", difference);
  for(i = 0; i < difference; i++){
    key[keyLen+i] = key[i];
  }
  keyLen = messageLen;
}

void chainer(unsigned char message[], unsigned char key[], int keyLen, int messageLen){
  //Encrypt key
  int sum = key[keyLen-1]%keyLen;
  int i = 0;
  //printf("Sum: %c", sum);
  //unsigned char chainedKey[keyLen];
  int bitOp = keyLen-1;
  for(i = 0; i < keyLen; i++){
    key[i] = rotate((key[i]^key[sum]),bits(key[bitOp]));
    sum+=key[i];
    sum = sum % keyLen;
    bitOp = i;
  }
}

void encrypt(unsigned char message[], unsigned char key[], int keyLen){
  int i = 0;
  for(i = 0; i < keyLen; i++){
    message[i] = key[i] ^ message[i];
  }
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
