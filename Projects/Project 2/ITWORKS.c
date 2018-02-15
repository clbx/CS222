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

struct lengthValues{                                                            //Im using a struct to help simplify the usage of the lengths between functions
                                                                                //This one stores the length of the message and the key
  int keyLen;                                                                   //This records the length of the key
  int messageLen;                                                               //This records the length of the message
};

                                                                                                         //Define our functions.
void printstr(unsigned char str[], int length);                                                          //This will print an array of characters.
void printints(unsigned char str[]);                                                                     //This will print an array of characters w/ interger values. Was used for input debugging.
int getLength(unsigned char str[]);                                                                      //This will output the length of said array, originally used for debugging but came in handy later.
int rotate(unsigned char character, int count);                                                          //This will rotate all but the most signifigant bit in a value.
int bits(unsigned char inputChar);                                                                       //This will output how many 1's are in the binary representation of a value.
struct lengthValues getInputs(unsigned char message[], unsigned char key[], struct lengthValues lengths);//This will get the inputs from the user and put them into the character arrays.
struct lengthValues tiler(unsigned char key[], struct lengthValues lengths);                             //This will ensure the key is as long as the message by repeating it until it is.
void chainer(unsigned char message[], unsigned char key[], struct lengthValues lengths);                 //This will run the chaining function to help strengthen the key encryption.
void encrypt(unsigned char message[], unsigned char key[], int keyLen);                                  //This will XOR each character in key and message against each other completing the encryption.



/*MAIN
   Description: This is the main function, the program starts here.
   Parameters:  none
   Returns:	    none
*/
int main(){
  unsigned char message[MAX_STR];                                               //This is the array of characters that holds the message.
  unsigned char key[MAX_STR];                                                   //This is the array of characters that holds the key
  struct lengthValues lengths = {0,0};                                          //This is a struct that holds the lengths of the key and message arrays
  lengths = getInputs(message, key, lengths);                                   //Getting the inputs from the user, and then updating the lengths
  if(lengths.keyLen < lengths.messageLen){                                      //If the key is shorter than the message, get the key to be longer using tiling
    lengths = tiler(key, lengths);                                              //Tile it, and then update the lengths
  }
  chainer(message, key, lengths);                                               //Using the chaining function, chain the key
  encrypt(message, key, lengths.keyLen);                                        //Now using the XOR encrypter encrypt the function
  printstr(message, lengths.keyLen);                                            //Now we let the world know
  return 0;                                                                     //All done.
}


/*INPUTS
   Description: This function gets the input from the user in a specific format
   of message -> delimiter -> key, then puts it in the message and key arrays
   Parameters:  message[]: the message array, key[]: the key array, lengths: the
   struct containing the lengths of message[] and key[]
   Returns:	    the new lengths of message[] and key[] in the struct lengths.
*/
struct lengthValues getInputs(unsigned char message[], unsigned char key[], struct lengthValues lengths){
  int inputChar = 0, flag = 1, i = 0;                                           //inputChar: our input varaible, flag: to flag if the input to message ended because of
                                                                                //the delimiter or EOF, i: an incrementing varaible.
  for(i = 0; (inputChar != 255) && (i < MAX_STR); i++){                         //This goes through the input until it sees 255 or reaches the max amount of characters allowed
    inputChar = getchar();                                                      //Get in the character from the input
    if(inputChar != EOF && inputChar != 255){                                   //Assuming the character isnt something we dont want
      message[i] = inputChar;                                                   //Put into into our message array
      lengths.messageLen++;                                                     //And make sure to update the lenthgs.
    }
    else if(inputChar == 255)                                                   //If it was the delimiter
      flag = 0;                                                                 //We want the program to know to know that it doesnt need to throw anything out
  }
  if(flag){                                                                     //If it wasnt the delimiter that ended the input
    int garbage;                                                                //Get a trash bag. garbage: a variable that's just collecting the rest of the input
    while(garbage != 255){                                                      //And until we reach the delimiter
      garbage = getchar();                                                      //Put it all in the garbage
    }
  }                                                                             //Wait for the truck to come? Though C doesnt have garbage collectiong does it.

  for(i = 0; (inputChar != EOF) && (lengths.keyLen < lengths.messageLen); i++){ //Now we move on to the key, this goes until it reaches the end or it's as long as the message
    inputChar = getchar();                                                      //Get the input from the user.
    if(inputChar != EOF){                                                       //Keep going until you hit the end of the file
      key[i] = inputChar;                                                       //Put it in the key array
      lengths.keyLen++;                                                         //And update the key length
    }
  }
  return lengths;                                                               //Give the lengths back then.
}

/*TILER
   Description: This function increases the key length by repeating itself until
   the key is just as long as the message
   Parameters:  key[]: the key array, lengths: the struct containing the lengths
   of message[] and key[]
   Returns:	    the new lengths of key[] in the struct lengths.
*/
struct lengthValues tiler(unsigned char key[], struct lengthValues lengths){
  int difference = lengths.messageLen - lengths.keyLen, i = 0;                  //difference: the difference between the key and the message. i: increment var
  for(i = 0; i < difference; i++){                                              //Run it as many times as the difference is to get key to be the same length as message
    key[lengths.keyLen+i] = key[i];                                             //Repeat the key with the beginning of the key
  }
  lengths.keyLen = lengths.messageLen;                                          //Message and key now are the same length
  return lengths;                                                               //Tell the world that they are the same now.
}

/*CHAINER
   Description: This function runs the chaining function for the key.
   Parameters:  key[]: the key array, lengths: the struct containing the lengths
   of message[] and key[]
   Returns:	    nothing
*/
void chainer(unsigned char message[], unsigned char key[], struct lengthValues lengths){
  int sum = key[lengths.keyLen-1]%lengths.keyLen;                               //sum: the running "total" of the accumulated characters, starts off with the last character
                                                                                //and is modded by the length to make sure it's always less than it.
  int i = 0;                                                                    //i: increment variable
  int bitOp = lengths.keyLen-1;                                                 //bitOp: the integer used in the "bits" function, it's originally set to the last character
                                                                                //Then is set to the previous element in the array for each element.
  for(i = 0; i < lengths.keyLen; i++){                                          //Go as long as the message/key is.
    key[i] = rotate((key[i]^key[sum]),bits(key[bitOp]));                        //Run the equation given for chaining
    sum+=key[i];                                                                //Update the sum
    sum = sum % lengths.keyLen;                                                 //Make sure the sum is still less than the length by modding it.
    bitOp = i;                                                                  //update the bit operator
  }
}

/* ENCRYPT
   Description: This function runs the XOR function for the final encrypt.
   Parameters:  message[]: the message being encrypted, key[] the key being used
   to encrypt, keylen: which is the length of both the message and key
   Returns:	    nothing
*/
void encrypt(unsigned char message[], unsigned char key[], int keyLen){
  int i = 0;                                                                    //i: increment variable.
  for(i = 0; i < keyLen; i++){                                                  //As long as the key/message is
    message[i] = key[i] ^ message[i];                                           //XOR the key and message together
  }
}

/* ROTATE
   Description: This function rotates the bits of a character
   Parameters:  character; the input character, count: the amount to shift it by
   Returns:	    The rotated character.
*/

int rotate(unsigned char character, int count){
	return (127 & ((character >> count) | (character <<(7 - count))));            //Shift the charater over, then & it so that the most significant digit is always 0
}

/* ROTATE
   Description: This function rotates the bits of a character
   Parameters:  character; the input character, count: the amount to shift it by
   Returns:	    The rotated character.
*/
int bits(unsigned char inputChar){
  int totalBits = 0;                                                            //totalBits: the total amount of '1' bits in a character
  while(inputChar){                                                             //While there is still something other than 0 left in the char
    totalBits += inputChar & 1;                                                 //see if the first bit is on or off
    inputChar >>= 1;                                                            //then shift
  }
  return totalBits;                                                             //Let the world know
}

/* PRINT STRING
   Description: This function prints out an array of charaters
   Parameters: str[] the input 'string', lenthg the length of the array
   Returns:	    nothing
*/
void printstr(unsigned char str[], int length){
  int i;                                                                        //i: increment variable
  for(i = 0; i < length; i++){                                                  //While it's less than the length
    putchar(str[i]);                                                            //Print the character at that element
  }
}
/*This function was used for testing purposes only

void printints(unsigned char str[]){
  printf("Printing Ints \n");
  int i;
  for(i = 0; str[i] != 0; i++){
    printf("%d ", str[i]);
  }
}
*/
