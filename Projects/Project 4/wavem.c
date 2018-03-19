#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void reverse(short* left, short* right, int lenLeft, int lenRight);
void changeSpeed(short** left, short** right, int lenLeft, int lenRight, double factor, WaveHeader* head);
void flip(short* left, short* right);
void swapValues(short* array, int index);
void fadeOut(short* left, short* right, int lenLeft, int lenRight, int duration);
void fadei(short* left, short* right, int lenLeft, int lenRight);
void changeVol(short* left, short* right, int lenLeft, int lenRight, int changeBy);
void echo(short* left, short* right, int lenLeft, int lenRight);





int main(int argc, char** argv){
	WaveHeader head;
	readHeader(&head);

	int i = 0;
	writeHeader(&head);

	short* left = (short*)malloc(sizeof(short)*head.dataChunk.size/4);
	short* right = (short*)malloc(sizeof(short)*head.dataChunk.size/4);

	char first;
	char second;
	short combined;
	int indexLeft = 0;
	int indexRight = 0;

	for(i = 1; i <= head.dataChunk.size/2; i++){
		first = getchar();
		second = getchar();
		combined = ((short)first) << 8;
		combined = combined | second;
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
	fprintf(stderr, "%d\n", head.dataChunk.size/2);

	//reverse(left, right, indexLeft, indexRight);
	//flip(left, right);
	//Need to output both halves of the short.
	//changeVol(left, right, indexLeft, indexRight, 50);
	changeSpeed(&left,&right,indexLeft,indexRight,1.49,&head);
	for(i = 0; i < head.dataChunk.size/2; i++){
		//char tempLeft = left[i];
		//char tempRight = right[i];
		printf("%c", (char)(left[i]>>8));
		printf("%c", (char)(left[i] & 0x00FF));
		printf("%c", (char)(right[i]>>8));
		printf("%c", (char)(right[i] & 0x00FF));
	}

	free(left);
	free(right);
	return 0;
}


void reverse(short* left, short* right, int lenLeft, int lenRight){
	swapValues(left, lenLeft);
	swapValues(right, lenRight);
}

void swapValues(short* array, int length){
	int i = 0;
	short temp;
	for(i = 0; i < length/2; i++){
		temp = array[i];
		array[i] = array[length-1-i];
		array[length-1-i] = temp;
	}
}

void changeSpeed(short** left, short** right, int lenLeft, int lenRight, double factor, WaveHeader* head){

	int newLength = lenLeft/factor;

	short* newLeft = (short*)malloc(sizeof(short)*newLength);
	short* newRight = (short*)malloc(sizeof(short)*newLength);

	int headerSize = head -> size - head -> dataChunk.size;
	head->dataChunk.size = newLength*2;
	head->size = head->dataChunk.size + headerSize;

	int i;
	for(i = 0; i < newLength; i++){
		newLeft[i] = (*left)[(int)(i*factor)];
		newRight[i] = (*right)[(int)(i*factor)];
	}

	writeHeader(head);
	free(*left);
	free(*right);
	*left = newLeft;
	*right = newRight;

}

void flip(short* left, short* right){
	short* temp = left;
	left = right;
	right = temp;
}
/*
void fadeOut(short* left, short* right, int lenLeft, int lenRight, int duration){
	int length = lenLeft;
	int sampleStart = length - 1 - 44100*duration;
	int i;
	for(i = sampleStart; i < length; i++)

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
