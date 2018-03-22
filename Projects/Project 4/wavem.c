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
	//Check if the file is RIFF, if not boot out.
	if(strncmp((const char*)head.ID, "RIFF", 4) != 0){
		fprintf(stderr, "File is not a RIFF file\n");
		return 1;
	}

	//Check if bad format chunk
	// ASK ABOUT THIS ONE

	if((strncmp((const char*)head.formatChunk.ID,"fmt ", 4) != 0) | (head.formatChunk.size != 16) | (head.formatChunk.compression != 1)){
		fprintf(stderr, "Format chunk is corrupted\n");
		return 1;
	}
	//Invalid Sample Rate
	else if(head.formatChunk.sampleRate != SAMPLERATE){
		fprintf(stderr, "File does not use 44,100Hz sample rate\n");
		return 1;
	}
	else if(head.formatChunk.bitsPerSample != 16){
		fprintf(stderr, "File does not have 16-bit samples\n");
		return 1;
	}
	else if(strncmp((const char*)head.dataChunk.ID, "data", 4) != 0){
		fprintf(stderr, "Format chunk is corrupted\n");
		return 1;
	}
	else if(head.formatChunk.channels != 2){
		fprintf(stderr, "File is not stereo\n");
		return 1;
	}


	int i = 0;

	int length = head.dataChunk.size/4;

	short* left = (short*)malloc(sizeof(short)*head.dataChunk.size/4);
	short* right = (short*)malloc(sizeof(short)*head.dataChunk.size/4);

	if((left == NULL)|(right == NULL)){
		fprintf(stderr, "Program out of memory\n");
	}

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

	if(indexLeft != length){
		fprintf(stderr, "File size does not match size in header\n");
		return 1;
	}
/*
	fprintf(stderr, "%d\n", indexLeft);
	fprintf(stderr, "%d\n", indexRight);
	fprintf(stderr, "%d\n", head.dataChunk.size/2);
*/


	i = 1;
	while(i < argc){
		if(strcmp(argv[i],"-r")==0){   //REVERSE, NO INPUTS
			reverse(left, right, &length);
			fprintf(stderr, "Audio reversed\n");
			i++;
		}
		else if(strcmp(argv[i],"-s")==0){ //SPEED, SCALE INPUT
			if(i+1 == argc){
				fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
				return 1;
			}
			i++;
			double factor = 0.0;
			factor = atof(argv[i]);
			if(factor <= 0.0){
				fprintf(stderr, "A positive number must be supplied for the speed change\n");
				return 1;
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
			if(i+1 == argc){
				fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
				return 1;
			}
			i++;
			double fadeTime = 0.0;
			fadeTime = atof(argv[i]);
			if(fadeTime <= 0.0){
				fprintf(stderr, "A positive number must be supplied for the fade in and fade out time\n");
				return 1;
			}
			fadeOut(left,right,&length,fadeTime);
			fprintf(stderr, "Fade out for %.2f seconds applied\n", fadeTime);
			i++;
		}
		else if(strcmp(argv[i],"-i")==0){ //FADE IN, TIME INPUT
			if(i+1 == argc){
				fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
				return 1;
			}
			i++;
			double fadeTime = 0.0;
			fadeTime = atof(argv[i]);
			if(fadeTime <= 0.0){
				fprintf(stderr, "A positive number must be supplied for the fade in and fade out time\n");
				return 1;
			}
			fadeIn(left,right,fadeTime);
			fprintf(stderr, "Fade in for %.2f seconds applied\n", fadeTime);
			i++;

		}
		else if(strcmp(argv[i],"-v")==0){ //VOLUME, CHANGE VOL INPUT
			if(i+1 == argc){
				fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
				return 1;
			}
			i++;
			double volScale = 0.0;
			volScale = atof(argv[i]);
			if(volScale <= 0.0){
				fprintf(stderr, "A positive number must be supplied for the volume scale\n");
				return 1;
			}
			changeVol(left,right,&length,volScale);
			fprintf(stderr, "Volume changed by x%.2f\n", volScale);
			i++;

		}
		else if(strcmp(argv[i],"-e")==0){ //ECHO, DELAY INPUT, SCALE INPUT
			if(i+1 == argc){
				fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
				return 1;
			}
			double delay = 0.0;
			double scale = 0.0;
			i++;
			delay = atof(argv[i]);
			i++;
			scale = atof(argv[i]);
			if((delay <= 0.0)|(scale <= 0.0)){
				fprintf(stderr, "Positive numbers must be supplied for the echo delay and scale parameters\n");
				return 1;
			}
			fprintf(stderr, "Echo created on a %.2f delay scaled to %.2f\n", delay, scale);
			echo(&left,&right,delay,scale,&length);
			i++;
		}
		else{
			fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
			return 1;
		}

	}

	head.dataChunk.size = length*4;
	head.size = head.dataChunk.size + 36;

	writeHeader(&head);

	for(i = 0; i < length; i++){
		putchar(left[i] & 0x00FF);
		putchar(left[i]>>8);
		putchar(right[i] & 0x00FF);
		putchar(right[i]>>8);

	}
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
	short* newLeft = (short*)malloc(sizeof(short)*newLength);
	short* newRight = (short*)malloc(sizeof(short)*newLength);
	if((newLeft == NULL)|(newRight == NULL)){
		fprintf(stderr, "Program out of memory\n");
	}

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

	for(i = sampleStart; i < *length; i++, n++){
		left[i] = (short)(left[i]*((double)(1.0-(n/samples))*(double)(1.0-(n/samples))));
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


void echo(short** left, short** right, double delay, double scale, int* length){
	int newLength = *length+(delay*SAMPLERATE);

	short* newRight = (short*)calloc(newLength, sizeof(short));
	short* newLeft = (short*)calloc(newLength, sizeof(short));


  //First copy in everything from the left and right into the new arrays
  int i;
	int j;

  for(i = 0; i < *length; i++){
      newLeft[i] = (*left)[i];
      newRight[i] = (*right)[i];
  }
	for(i = delay*SAMPLERATE, j = 0; i < newLength && j < *length ; i++,j++){
		newLeft[i] = (short)(newLeft[i]+(*left)[j]*scale);
		newRight[i] = (short)(newRight[i]+(*right)[j]*scale);
	}

	*length = newLength;
	free(*left);
	free(*right);
	*left = newLeft;
	*right = newRight;

}