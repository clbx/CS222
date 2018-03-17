#include <stdio.h>
#include <stdlib.h>

void merge(int array1[], int length1, int array2[], int length2, int result[]);



int main(){
  int length1= 0, length2 = 0;
  scanf("%d", &length1);
  scanf("%d", &length2);

  int* array1 = (int*)malloc(sizeof(int)*length1);
  int* array2 = (int*)malloc(sizeof(int)*length2);
  int* result = (int*)malloc(sizeof(int)*(length1+length2));

  int i = 0;
  for(i = 0; i < length1; i++){
    scanf("%d", &array1[i]);
  }
  for(i = 0; i < length2; i++){
    scanf("%d", &array2[i]);
  }
  printf("List 1:");
  for(i = 0; i < length1; i++){
    printf("%d ", array1[i]);
  }
  printf("\n");
  printf("List 2:");
  for(i = 0; i < length2; i++){
    printf("%d ", array2[i]);
  }
  printf("\n");

  merge(array1, length1, array2, length2, result);

	printf("Merged List: ");
	for(i = 0; i < length1 + length2; i++){
		printf("%d ", result[i]);
	}

	free(array1);
	free(array2);
	free(result);


  return 0;
}


void merge(int array1[], int length1, int array2[], int length2, int result[]){

	int i = 0;
  int index1 =0, index2 = 0;
  for(i = 0; i < length1 + length2; i++){

		if(index2 >= length2){
			result[i] = array1[index1];
      index1++;
		}
		else if((index1 >= length1) || (array1[index1] > array2[index2]) ){
			result[i] = array2[index2];
      index2++;
		}
    else{
      result[i] = array1[index1];
      index1++;
    }

  }






}
