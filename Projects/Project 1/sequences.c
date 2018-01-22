#include <stdio.h>

//Caterer's Equation
int caterer(int in){
  int out;
  out = ((in*in)+(in+2))/2;
  return out;
}



int main(){
  //Some Re-Used Variales.
  int i;
  double result;

  //Lazy Caterer's Sequence.
  printf("Lazy Caterer's Sequence\n");
  for(i = 0; i < 50; i++){
    result = caterer(i);
    printf("%G ", result);
  }
  printf("\n");

  //Prime Numbers.
  //Fibonacci Sequence.
  //Collatz Stopping Times.
  //Happy Numbers.

}
