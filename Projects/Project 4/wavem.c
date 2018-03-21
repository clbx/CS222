#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define SAMPLERATE 44100

void reverse(short* left, short* right, int* length);
void changeSpeed(short** left, short** right, double factor, int* length);
void flip(short** left, short** right);
void swapValues(short* array, int index);
void fadeOut(short* left, short* right, int* length,double duration);
void fadeIn(short* left, short* right,double duration);
void changeVol(short* left, short* right, int* length, double changeBy);
void echo(short** left, short** right, double delay, double scale, int* length);
void volScale(short* array, int length, double changeBy);


int main(int argc, char** argv){
	WaveHeader head;
	readHeader(&head);




	//ERROR CHECKING
	//fprintf(stderr, "%s\n", head.ID);
	//Check if the file is RIFF
	if(strncmp((const char*)head.ID, "RIFF", 4)){
		fprintf(stderr, "File is not a RIFF file\n");
		return 0;
	}

	//Check if bad format chunk
	// ASK ABOUT THIS ONE
	/*
	fprintf(stderr, "%s\n", head.formatChunk.ID);
	if(strcmp((const char*)head.formatChunk.ID, "fmt ")){
		//fprintf(stderr, "%s\n", strstr((const char*)head.formatChunk.ID, "fmt"));
		fprintf(stderr, "Format Chunk is Corrupted\n");
		return 0;
	}
	*/


	//Invalid Sample Rate
	else if(head.formatChunk.sampleRate != 44100){
		fprintf(stderr, "File does not use 44,100Hz sample rate\n");
		return 0;
	}
	else if(head.formatChunk.bitsPerSample != 16){
		fprintf(stderr, "File does not have 16-bit samples\n");
	}
	int i = 0;

	int length = head.dataChunk.size/4;

	short* left = (short*)malloc(sizeof(short)*head.dataChunk.size/4);
	short* right = (short*)malloc(sizeof(short)*head.dataChunk.size/4);


	unsigned char first;
	unsigned char second;
	short combined;
	int indexLeft = 0;
	int indexRight = 0;

	//READING IN
	for(i = 1; i <= head.dataChunk.size/2; i++){
		first = getchar();
		second = getchar();
		combined = (second) << 8;
		combined = combined | first;
		if(i%2 == 0){  //THIS IS GOING TO BE REMOVED/CHANGED
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

	i = 1;
	while(i < argc){
		if(strcmp(argv[i],"-r")==0){   //REVERSE, NO INPUTS
			reverse(left, right, &length);
			fprintf(stderr, "Audio reversed\n");
			i++;
		}
		else if(strcmp(argv[i],"-s")==0){ //SPEED, SCALE INPUT
			i++;
			double factor = atof(argv[i]);
			if(factor < 0){
				fprintf(stderr, "A positive number must be supplied for the speed change\n");
				return 0;
			}
			fprintf(stderr, "Speed changed by x%.2f\n", factor);
			changeSpeed(&left,&right,factor,&length);
			i++;

		}
		else if(strcmp(argv[i],"-f")==0){ //FLIP, NO INPUTS
			flip(&left, &right);
			fprintf(stderr, "Channels flipped\n");
			i++;
		}
		else if(strcmp(argv[i],"-o")==0){ //FADE OUT, TIME INPUT
			i++;
			double fadeTime = atoi(argv[i]);
			if(fadeTime < 0){
				fprintf(stderr, "A positive number must be supplied for the fade in and fade out time\n");
				return 0;
			}
			fadeOut(left,right,&length,fadeTime);
			fprintf(stderr, "Fade out for %.2f seconds applied\n", fadeTime);
			i++;
		}
		else if(strcmp(argv[i],"-i")==0){ //FADE IN, TIME INPUT
			i++;
			double fadeTime = atoi(argv[i]);
			if(fadeTime < 0){
				fprintf(stderr, "A positive number must be supplied for the fade in and fade out time\n");
				return 0;
			}
			fadeIn(left,right,fadeTime);
			fprintf(stderr, "Fade in for %.2f seconds applied\n", fadeTime);
			i++;

		}
		else if(strcmp(argv[i],"-v")==0){ //VOLUME, CHANGE VOL INPUT
			i++;
			double volScale = atoi(argv[i]);
			changeVol(left,right,&length,volScale);
			fprintf(stderr, "Volume changed by x%.2f\n", volScale);
			i++;

		}
		else if(strcmp(argv[i],"-e")==0){ //ECHO, DELAY INPUT, SCALE INPUT
			i++;
			double delay = atoi(argv[i]);
			i++;
			double scale = atoi(argv[i]);
			if((delay < 0)|(scale < 0))
				fprintf(stderr, "Positive numbers must be supplied for the echo delay and scale parameters\n");
			fprintf(stderr, "Echo created on a %.2f delay scaled to %.2f\n", delay, scale);
			echo(&left,&right,delay,scale,&length);
			i++;

		}
		else{
			fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
			return 0;
		}

	}

	//reverse(left, right, &length);
	//Need to output both halves of the short.
	//changeVol(left, right, &length, .5);
	//changeSpeed(&left,&right,2.43,&length);
	//fadeIn(left, right,5.0);
	//flip(&left,&right);
	//fprintf((stderr), "%d\n", head.size - head.dataChunk.size);
	//echo(&left,&right,.2,3,&length);


	head.dataChunk.size = length*4;
	head.size = head.dataChunk.size + 36;


	writeHeader(&head);

	for(i = 0; i < length; i++){
		//char tempLeft = left[i];
		//char tempRight = right[i];
		putchar(left[i] & 0x00FF);
		putchar(left[i]>>8);
		putchar(right[i] & 0x00FF);
		putchar(right[i]>>8);

	}
	fprintf(stderr, "HERE!!!!!!!!!!\n" );
	free(left);
	free(right);

	return 0;
}


void reverse(short* left, short* right, int* length){
	swapValues(left, *length);
	swapValues(right, *length);
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

void changeSpeed(short** left, short** right, double factor, int* length){

	int newLength = *length/factor;
	fprintf(stderr, "FIRST\n");
	short* newLeft = (short*)malloc(sizeof(short)*newLength);
	short* newRight = (short*)malloc(sizeof(short)*newLength);

	int i;
	for(i = 0; i < newLength; i++){
		newLeft[i] = (*left)[(int)(i*factor)];
		newRight[i] = (*right)[(int)(i*factor)];
	}

	*length = newLength;
	free(*left);
	free(*right);
	*left = newLeft;
	*right = newRight;
	fprintf(stderr, "LAST\n");

}

void flip(short** left, short** right){
	short* temp = *left;
	*left = *right;
	*right = temp;
}

void fadeOut(short* left, short* right, int* length, double duration){
	int sampleStart = *length - SAMPLERATE*duration;
	double samples = (duration*SAMPLERATE);
	int n = 0;
	int i;
	double fade = 0;

	for(i = sampleStart; i < *length; i++, n++){
		fprintf(stderr, "%d ", left[i]);
		left[i] = (short)(left[i]*((double)(1.0-(n/samples))*(double)(1.0-(n/samples))));
		fprintf(stderr, "%d\n", left[i]);
		right[i] = (short)(right[i]*((double)(1.0-(n/samples))*(double)(1.0-(n/samples))));
	}
}

void fadeIn(short* left, short* right, double duration){
	double i;
	double samples = (duration * SAMPLERATE);
	double fade = 0;

	for(i = 0; i < samples; i++){
		fade = ((i/samples)*(i/samples));
		left[(int)i] = (left[(int)i]*fade);
		right[(int)i] = (right[(int)i]*fade);

	}
}


void volScale(short* array, int length, double changeBy){
	int i = 0;
	for(i = 0; i < length; i ++){
		if(array[i]*changeBy >= SHRT_MAX)
			array[i] = SHRT_MAX;
		else if(array[i]*changeBy <= SHRT_MIN)
			array[i] = SHRT_MIN;
		else
			array[i] = (short)(array[i]*changeBy);
	}
}


void changeVol(short* left, short* right, int* length, double changeBy){

	volScale(left,*length,changeBy);
	volScale(right,*length,changeBy);

}

//NEEDS WORK
void echo(short** left, short** right, double delay, double scale, int* length){
	int newLength = *length+(delay*SAMPLERATE);


  //short* newRight = (short*)malloc(sizeof(short)*(newLength));
  //short* newLeft = (short*)malloc(sizeof(short)*(newLength));
	short* newRight = (short*)calloc(newLength, sizeof(short));
	short* newLeft = (short*)calloc(newLength, sizeof(short));


  //First copy in everything from the left and right into the new arrays
  fprintf(stderr, "HERE1\n");
  int i;
	int j;

  for(i = 0; i < *length; i++){
      newLeft[i] = (*left)[i];
      newRight[i] = (*right)[i];
			/*
      fprintf(stderr, "%d ", newLeft[i]);
      fprintf(stderr, "%d ", (*left)[i]);
      fprintf(stderr, "%d\n",i);*/
  }
	for(i = delay, j =0; i < newLength && j < *length ; i++,j++){
		newLeft[i] = (short)(newLeft[i]+(*left)[j]*scale);
		newRight[i] = (short)(newRight[i]+(*right)[j]*scale);
	}



	*length = newLength;
	free(*left);
	free(*right);
	*left = newLeft;
	*right = newRight;

}