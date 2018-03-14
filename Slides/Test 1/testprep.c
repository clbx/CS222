#include <stdio.h>

char repeats(char string[]);


int main(){
  char word[] = "Hellooooooo Lady";
  printf("%d", repeats(word));
}

char repeats(char string[]){
  int length = 0;
  while(string[length] != '\0'){
    length++;
  }
  int i = 0, localmax = 1, totalmax = 1;
  for(i = 0; i < length -1; i++){
    if(string[i] == string[i+1]){
      localmax++;
    }
    else
      localmax = 1;
    if(localmax > totalmax){
      totalmax = localmax;
    }
  }
  return totalmax;
}
