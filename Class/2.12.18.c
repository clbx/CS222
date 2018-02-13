#include <stdio.h>

void reverse(int values[], int size);
void print(int values[], int size);

int main(){
  int values[100];
  int i = 0;
  for(i = 0; i < 100; ++i){
    values[i] = i + 1;
  print(values, 100);
  reverse( values, 100);
  print(values, 100);
  }
}

void reverse(int values[], int size){
  int i = 0;
  for(i = 0; i < size/2; i++){
    int temp = values[i];
    values[i] = values[size-i-1];
    values[size - i - 1] = temp;
  }
}

void print(int values[], int size){
  int i = 0;
  for(i = 0; i < size; i ++){
    printf("%d ", values[i]);
  }
  printf("\n");


}
