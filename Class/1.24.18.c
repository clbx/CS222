#include <stdio.h>
#include <math.h>

int main(){
  double x=1;
  double y=5;
  double angle = atan2(y,x);
  printf("Shoot at: %f", angle);

  return 0;
}
