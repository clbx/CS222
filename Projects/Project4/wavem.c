#include "wave.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv){
	WaveHeader head;
	readHeader(&head);

	int i = 0;
	writeHeader(&head);

	short* left = malloc(sizeof(short)*head.size/2);
	short* right = malloc(sizeof(short)*head.size/2);

	char first;
	char second;
	char combined;
	int indexLeft = 0;
	int indexRight = 0;

	for(i = 1; i <= head.size; i++){
		first = getchar();
		second = getchar();

		first = first << 8;
		combined = first | second;
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

	for(i = 0; i < indexLeft; i++){
		putchar(left[i]);
		putchar(left[i]);
		putchar(left[i]);
		putchar(left[i]);
	}


	free(left);
	free(right);
	return 0;
}
/*
void reverse(short* left, short* right){

}

void change(short* left, short* right){

}

void flip(short* left, short* right){

}

void fadeo(short* left, short* right){

}

void fadei(short* left, short* right){

}

void vol(short* left, short* right){

}

void echo(short* left, short* right){

}*/
