#include <stdio.h>
#include <string.h>

void makeLower(char* letter);

int main(){

  char word[] = "Emacs is great, Mighty Joe Young";
  int length = strlen(word);

  int i = 0;
  for(i = 0; i< length; i++){
    makeLower(&word[i]);
  }
  char thing = 'P';
  printf("%c",thing);
  makeLower(&thing);
  printf("%c",thing);
  printf("%s", word);
  return 0;
}

void makeLower(char * letter){
  if(*letter >= 'A' && *letter <= 'Z')
    *letter += 'a' - 'A';
}
