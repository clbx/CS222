#include <stdio.h>

int main(){

  printf("%d",EOF);

  int c = getchar();

  if((c = getchar()) != EOF){
    putchar(c);
  }


}
