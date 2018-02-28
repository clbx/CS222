#include <stdio.h>
#include <stdlib.h>


int main(){

  printf("Enter the size of the list");
  int size = 0;
  scanf("%d", &size);

  int* array = (int*)malloc(sizeof(int)*size);

  int i = 0;
  for(i = 0; i < size; i++){
    printf("Enter element %d: ", i+1);
    scanf("%d", &array[i]);
  }
  //Sort.
  for(i = 0; i < size - 1; i++){
    int small = i;
    int j;
    for(j = i + 1; j < size; j++){
      if(array[j] < array[small]){
        small = j;
      }
    }
    int temp = array[small];
    array[small] = array[i];
    array[i] = temp;
  }
  free(array);
  return 0;
}
