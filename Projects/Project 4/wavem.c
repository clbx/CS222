//Should 4 characters or 2.


#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void reverse(short* left, short* right, int lenLeft, int lenRight);
void changeSpeed(short* left, short* right, int lenLeft, int lenRight);
void flip(short* left, short* right);
short* swapValues(short* array, int index);
void fadeo(short* left, short* right, int lenLeft, int lenRight);
void fadei(short* left, short* right, int lenLeft, int lenRight);
void changeVol(short* left, short* right, int lenLeft, int lenRight, int changeBy);
void echo(short* left, short* right, int lenLeft, int lenRight);




int main(int argc, char** argv){
	WaveHeader head;
	readHeader(&head);

	int i = 0;
	writeHeader(&head);

	short* left = (short*)malloc(sizeof(short)*head.size/2);
	short* right = (short*)malloc(sizeof(short)*head.size/2);

	char first;
	char second;
	short combined;
	int indexLeft = 0;
	int indexRight = 0;

	for(i = 1; i <= head.size; i++){
		//
		first = getchar();
		second = getchar();
		combined = ((short)first) << 8;
		combined = combined | second;
		//
		if(i%2 == 0){
			right[indexRight] = combined;
			indexRight++;
		}
		else{
			left[indexLeft] = combined;
			indexLeft++;
		}
	}

	fprintf(stderr, "%d\n", indexLeft);
	fprintf(stderr, "%d\n", indexRight);
	fprintf(stderr, "%d\n", head.size/2);

	//reverse(left, right, indexLeft, indexRight);
	changeVol(left, right, indexLeft, indexRight, 50);
	for(i = 0; i < indexLeft; i++){
		printf("%c", left[i]);
		printf("%c", left[i]);
		printf("%c", right[i]);
		printf("%c", right[i]);
	}

	free(left);
	free(right);
	return 0;
}



void reverse(short* left, short* right, int lenLeft, int lenRight){
	/*int i = 0;
	for(i = 0; i < lenLeft-1; i++)
		fprintf(stderr, "%d", left[i]);*/
	left = swapValues(left, lenLeft);
	right = swapValues(right, lenRight);
}

short* swapValues(short* array, int length){
	int i = 0;
	short* tempArray = (short*)malloc(sizeof(short)*length);
	for(i = 0; i < length-1; i++){
		tempArray[i] = array[length-1-i];
		//fprintf(stderr, "%c\n", tempArray[i]);
		//fprintf(stderr, "%c\n", array[length-1-i]);
	}
	return tempArray;
	free(tempArray);
}
/*
void changeSpeed(short* left, short* right, int lenLeft, int lenRight){

}

void flip(short* left, short* right){
	short* temp = left;
	left = right;
	right = temp;
}

void fadeo(short* left, short* right, int lenLeft, int lenRight){

}

void fadei(short* left, short* right, int lenLeft, int lenRight){

}
*/
void changeVol(short* left, short* right, int lenLeft, int lenRight, int changeBy){
	int i = 0;
	int max = SHRT_MAX;
	int min = SHRT_MIN;
	for(i = 0; i < lenLeft; i ++){
		if(left[i]*changeBy >= max)
			left[i] = max;
		else if(left[i]*changeBy <= min)
			left[i] = min;
		else
			left[i] = left[i]*changeBy;
	}
	for(i = 0; i < lenRight; i ++){
		if(right[i]*changeBy >= max)
			right[i] = max;
		else if(right[i]*changeBy <= min)
			right[i] = min;
		else
			right[i] = right[i]*changeBy;
	}

}
/*
void echo(short* left, short* right, int lenLeft, int lenRight){

}*/
