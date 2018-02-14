#include <stdio.h>


int readInt(){
	int c = 0;
	int i = 0;

	while( (c = getchar()) != EOF && c != '\n' ){
		if( c >= '0' && c <= '9')
			i = i * 10 + (c - '0');
    else if((c = '\n')){
    }
	}
	return i;
}

void selectionSort(int array[], int size){
	int i = 0;
	for(i = 0; i < size; i++){
		int j = 0;
		int small = i;
		for(j = i + 1; j < size; j++){
			if(array[j] < array[small]){
				small = j;

				int temp = array[i];
				array[i] = array[small];
				array[small] = temp;
			}
		}
	}

}

int main(){
  int values[100];
  int size = 0;

  do{
    printf("Please enter a int between 0 and 100: ");
    size = readInt();
  }while(size > 100);

  printf("Enter %d positive integers:\n", size);
  int i = 0;
  for(i = 0; i < size; i++){
    values[i] = readInt();
  }

  int min = values[0], max = values[0];
  int total = 0;

  for(i = 1; i < size; i++){
    if(max < values[i])
      max = values[i];
    if(min > values[i])
      min = values[i];
    total += values[i];
  }
  double avg = total/size;

  printf("Max %d, Min %d, Avg, %f\n", max, min, avg);

	double variance = 0;

	for(i = 0; i < size; i++){
		variance += (values[i] - avg)*(values[i] - avg);
	}
	variance /= size-1;
	printf("Variance: %f", variance);

	//Median

	



}
