#include <stdio.h>

int main(){
  double nc;

  nc = 0;
  while (getchar() != EOF) {
    ++nc;
  }
  printf("%0.1f\n ", nc);
}
