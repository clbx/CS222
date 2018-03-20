#include "wave.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define SAMPLERATE 44100

void reverse(short* left, short* right, int lenLeft, int lenRight);
void changeSpeed(short** left, short** right, int lenLeft, int lenRight, double factor, WaveHeader* head);
void flip(short* left, short* right);
void swapValues(short* array, int index);
void fadeOut(short* left, short* right, int lenLeft, int lenRight, double duration);
void fadeIn(short* left, short* right, int lenLeft, int lenRight, double duration);
void changeVol(short* left, short* right, int lenLeft, int lenRight, int changeBy);
void echo(short* left, short* right, int lenLeft, int lenRight, double delay, double scale);



int main(int argc, char** argv){
	WaveHeader head;
	readHeader(&head);

	//ERROR CHECKING
	//fprintf(stderr, "%s\n", head.ID);
	//Check if the file is RIFF
	if(strcmp((const char*)head.ID, "RIFF")){
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


	//COMMAND HANDLING


	i = 1;
	while(i < argc){
		if(strcmp(argv[i],"-r")==0){   //REVERSE, NO INPUTS
			//reverse(left, right, indexLeft, indexRight);
			fprintf(stderr, "Audio reversed\n");
			i++;
		}
		else if(strcmp(argv[i],"-s")==0){ //SPEED, SCALE INPUT
			i++;
			double speedChange = atof(argv[i]);
			if(speedChange < 0){
				fprintf(stderr, "A positive number must be supplied for the speed change\n");
				return 0;
			}
			fprintf(stderr, "Speed changed by x%.2f\n", speedChange);
			//changeSpeed(&left,&right,indexLeft,indexRight,speedChange,&head);
			i++;

		}
		else if(strcmp(argv[i],"-f")==0){ //FLIP, NO INPUTS
			//flip(left*, right*);
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
			//fadeOut(left, right, indexLeft, indexRight, fadeTime);
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
			//fadeIn(left, right, indexLeft, indexRight, fadeTime);
			fprintf(stderr, "Fade in for %.2f seconds applied\n", fadeTime);
			i++;

		}
		else if(strcmp(argv[i],"-v")==0){ //VOLUME, CHANGE VOL INPUT
			i++;
			double volScale = atoi(argv[i]);
			changeVol(left, right, indexLeft, indexRight, volScale);
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
			echo(left, right, indexLeft, indexRight, delay, scale);
			i++;

		}
		else{
			fprintf(stderr, "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n");
			return 0;
		}

	}
	return 0;

	//reverse(left, right, indexLeft, indexRight);
	//Need to output both halves of the short.
	//changeVol(left, right, indexLeft, indexRight, 50);
	//changeSpeed(&left,&right,indexLeft,indexRight,1.49,&head);
	fadeIn(left, right, indexLeft, indexRight, 4.0);
	writeHeader(&head);

	for(i = 0; i < indexLeft; i++){
		//char tempLeft = left[i];
		//char tempRight = right[i];
		printf("%c", (char)(left[i]>>8));
		printf("%c", (char)(left[i] & 0x00FF));
		printf("%c", (char)(right[i]>>8));
		printf("%c", (char)(right[i] & 0x00FF));
	}
	fprintf(stderr, "HERE!!!!!!!!!!\n" );
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

void flip(short** left, short** right){
	short* temp = *left;
	*left = *right;
	*right = temp;
}

void fadeOut(short* left, short* right, int lenLeft, int lenRight, double duration){
	int length = lenLeft;
	int sampleStart = length - SAMPLERATE*duration;
	int samples = (int)(duration*SAMPLERATE);
	double n = 0;
	int i;
	double fade = 0;

	if(duration < samples){
		samples = length;
	}

	if( sampleStart < 0){
		sampleStart = 0;
	}

	fprintf(stderr, "HERE\n");
	for(i = sampleStart; i < length; i++, n++){
		fade = (1.0 - n/(samples-1))*(1.0 -n/(samples-1));
		left[i] = (left[i]*fade);
		right[i] = (right[i]*fade);
	}
	fprintf(stderr, "HERE?\n");


}

void fadeIn(short* left, short* right, int lenLeft, int lenRight, double duration){
	double i;
	double samples = (int)(duration * SAMPLERATE);
	double fade = 0;

	for(i = 0; i < samples; i++){
		fade = ((1.0)*(i/samples))*((1.0)*(i/samples));
		left[(int)i] = (left[(int)i]*fade);
		right[(int)i] = (right[(int)i]*fade);

	}
}


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

void echo(short* left, short* right, int lenLeft, int lenRight, double delay, double scale){
	/*
	short* newLeft = (short*)malloc(sizeof(short)*(lenLeft+(dealy*SAMPLERATE)));
	short* newRight = (short*)malloc(sizeof(short)*(lenRight+(delay*SAMPLERATE)));

	int start =
	*/

}
