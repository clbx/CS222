/*==================

Lab 1: Stars
Clay Buxton (1/19/18)

===================*/

#include <stdio.h>

int main(){
  int i;
  int j;

  for(i = 1; i <= 10; i++){
    for(j = 0; j < i; j++){
      printf("*");
    }
    printf("\n");
  }
}
