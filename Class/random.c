#include <stdio.h>

int main(){
  int i = 0;
  for(i = 0; i < 10; i++){
    printf("%d\n", rand() %3 -1);
  }
  return 0;
}
