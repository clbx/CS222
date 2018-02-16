#include <stdio.h>
#include <string.h>

int main(){
  char string[1024];
  int inputChar;
  int length = 0;
  int i = 0;
  printf("Enter a string: ");
  inputChar = getchar();
  for(i = 0; i < 1024 && inputChar != '\n'; i++){
    string[i] = inputChar;
    inputChar = getchar();
    length++;
  }
  string[length] = '\0';
  //Copy this string and save it for later
  char temp[length];
  for(i = 0; i < length; i++){
    temp[i] = string[i];
  }
  temp[length] = '\0';

  //Then we get it all to lowercase:
  int difference = 'A'-'a';
  for(i = 0; i < length; i++){
    if(string[i] >= 'A' && string[i] <= 'Z'){
      string[i] = string[i] - difference;
    }
  }
  //Then we reverse the string into a new string
  //printf("%s\n", string);
  int j = 0;
  char reverse[length];
  for(int i = length-1; i >= 0; i--){
    reverse[i] = string[j];
    j++;
  }
  reverse[length] = '\0';
  //printf("%s\n", reverse);
  //Now we check if it's a palindrome
  int flag = 1;
  for(i = 0; i < length && flag; i++){
    if(reverse[i] != string[i]){
      printf("The string \"%s\" is not a palindrome", temp);
      flag = 0;
    }
  }
  if(flag){
    printf("The string \"%s\" is a palindrome", temp);
  }




}
