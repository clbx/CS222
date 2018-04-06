#include <stdio.h>
#include <stdlib.h>


int main(){
  printf("What is the file name? ");
  char filename[255];

  scanf("%s", filename);

  FILE* file = fopen(filename, "rb");

  int n;
  fread(&n, sizeof(int), 1, file);
  int sum = 0;

  int* array = (int*)malloc(sizeof(int)*n);
  fread(array, sizeof(int), 1, file);


  int i = 0;
  for(i = 0; i < n; ++i){
    int value;
    fscanf(file, "%d", value);
    sum += value;
  }
}
