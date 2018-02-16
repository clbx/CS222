#include <stdio.h>
#include <string.h>

void print(char word[], int length){
  int i;
  for(i = 0; i < length; i ++){
    putchar(word[i]);
  }
}

int main(){
  char word1[1024];
  char word2[1024];

  strcpy(word1, "These are the times");
  strcpy(word2, word1);

  printf("Word1: %s\n", word1);
  printf("Word2: %s\n", word2);

  strcat(word1, " that try men's souls");
  printf("Word1: %s\n", word1);
}
