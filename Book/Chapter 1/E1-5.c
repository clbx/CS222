#include <stdio.h>

/* Print F->Table for Fhar = 0, 20, ..., 300*/

int main(){
  int fahr;
  for(fahr = 300; fahr >=0; fahr = fahr - 20){
    printf("%3d %6.1f\n", fahr, (5.0/9.0)*fahr-32);
  }
}
