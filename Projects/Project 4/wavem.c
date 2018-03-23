/*******************************
*
*  Project Name: Project 4: Wave Goodbye
*  Description: Maninpulating wav files to do cool things, such as fades, echos, change speeds,and reversing
*  File names: wave.c wave.h *.wav
*  Date: 03/23/2018
*  Authors: Clay Buxton and Austin Reth
*
*******************************/
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
void fadeIn(short* left, short* right, int* length, double duration);
void changeVol(short* left, short* right, int* length, double scale);
void echo(short** left, short** right, double delay, double scale, int* length);
void volumeScale(short* array, int length, double scale);
void readShort(short* array, int index);

int main(int argc, char** argv){
	WaveHeader head;
	readHeader(&head);

	//Check if the file is RIFF, if not boot out.
	if(strncmp((const char*)head.ID, "RIFF", 4) != 0){
		fprintf(stderr, "File is not a RIFF file\n");
		return 1;
	}
	//Check if bad format chunk
	if((strncmp((const char*)head.formatChunk.ID,"fmt ", 4) != 0) | (head.formatChunk.size != 16) | (head.formatChunk.compression != 1)){
		fprintf(stderr, "Format chunk is corrupted\n");
		return 1;
	}
	//Invalid Sample Rate
	else if(head.formatChunk.sampleRate != SAMPLERATE){
		fprintf(stderr, "File does not use 44,100Hz sample rate\n");
		return 1;
	}
	//Wrong sample size
	else if(head.formatChunk.bitsPerSample != 16){
		fprintf(stderr, "File does not have 16-bit samples\n");
		return 1;
	}
	//Check dataChunk ID
	else if(strncmp((const char*)head.dataChunk.ID, "data", 4) != 0){
		fprintf(stderr, "Format chunk is corrupted\n");
		return 1;
	}
	//Make sure there are 2 channels
	else if(head.formatChunk.channels != 2){
		fprintf(stderr, "File is not stereo\n");
		return 1;
	}

	int i = 0;
	int length = head.dataChunk.size/4;

	short* left = (short*)malloc(sizeof(short) * head.dataChunk.size / 4);
	short* right = (short*)malloc(sizeof(short) * head.dataChunk.size / 4);

	if((left == NULL) | (right == NULL)){
		fprintf(stderr, "Program out of memory\n");
	}

	int index = 0;

	for(i = 0; i < head.dataChunk.size / 4; i++){
		readShort(left, index);
		readShort(right, index);
		index++;
	}
	if(index != length){
		fprintf(stderr, "File size does not match size in header\n");
		return 1;
	}

	//COMMAND STRUCTURE
	char commandError[] = "Usage: wave [[-r][-s factor][-f][-o delay][-i delay][-v scale][-e delay scale] < input > output\n";
	i = 1;
	while(i < argc){
		//REVERSE
		if(strcmp(argv[i],"-r") == 0){																							//Check for Reverse (-r)
			reverse(left,right,&length);
			fprintf(stderr, "Audio reversed\n");
			i++;
		}
		//CHANGE SPEED
		else if(strcmp(argv[i],"-s") == 0){ 																				//Check for Change Speed (-s)
			if(i + 1 == argc){																												//If this is the last element of the command array
				fprintf(stderr, "%s", commandError);																		//Print out the error
				return 1;																																//And exit
			}
			i++;
			double factor = 0.0;
			factor = atof(argv[i]);
			if(factor <= 0.0){																												//If the output of the atof function is 0.0, that means it was not a number
																																								//And we only want numbers.
				fprintf(stderr, "A positive number must be supplied for the speed change\n");    //Print out the error
				return 1;																																//And exit
			}
			fprintf(stderr, "Speed changed by x%.2f\n", factor);
			changeSpeed(&left,&right,factor,&length);
			i++;
		}
		//FLIP CHANNELS
		else if(strcmp(argv[i],"-f") == 0){
			flip(&left,&right);
			fprintf(stderr, "Channels flipped\n");
			i++;
		}
		//FADE OUT
		else if(strcmp(argv[i],"-o") == 0){
			if(i + 1 == argc){																												//Check if it's the last thing in the array
				fprintf(stderr, "%s", commandError);																		//If it is, then print out the error
				return 1;																																//And exit
			}
			i++;
			double fadeTime = 0.0;
			fadeTime = atof(argv[i]);
			if(fadeTime <= 0.0){																											//if the fade time is 0.0 OR less than 0
				if(fadeTime < 0.0){																											//Check if its less than 0 then
					fprintf(stderr, "A positive number must be supplied for the fade in and fade out time.\n");
					return 1;																															//If it's less than 0, its an invalid numer
				}
				fprintf(stderr, "%s", commandError);																		//But if it's 0.0, that means the atoi didnt read it in as a number
				return 1;
			}
			fadeOut(left,right,&length,fadeTime);
			fprintf(stderr, "Fade out for %.2f seconds applied\n", fadeTime);
			i++;
		}
		//FADE IN
		else if(strcmp(argv[i],"-i") == 0){
			if(i + 1 == argc){																												//Check if it's the last thing in the array
				fprintf(stderr, "%s", commandError);																		//If it is, then print out the error
				return 1;																																//And exit
			}
			i++;
			double fadeTime = 0.0;
			fadeTime = atof(argv[i]);
			if(fadeTime <= 0.0){																											//if the fade time is 0.0 OR less than 0
				if(fadeTime < 0.0){																											//Check if its less than 0 then
					fprintf(stderr, "A positive number must be supplied for the fade in and fade out time.\n");
					return 1;																															//If it's less than 0, its an invalid numer
				}
				fprintf(stderr, "%s", commandError);																		//But if it's 0.0, that means the atoi didnt read it in as a number
				return 1;
			}
			fadeIn(left,right,&length,fadeTime);
			fprintf(stderr, "Fade in for %.2f seconds applied\n", fadeTime);
			i++;
		}
		//CHANGE VOLUME
		else if(strcmp(argv[i],"-v") == 0){
			if(i + 1 == argc){																												//Check to see if its the last element
				fprintf(stderr, "%s", commandError);
				return 1;
			}
			i++;
			double volumeScale = 0.0;
			volumeScale = atof(argv[i]);
			if(volumeScale <= 0.0){																										//As with fade in and out, check to see if its 0 or less than
				if(volumeScale < 0.0){																									//If it's less than 0, then it's not a correct input
					fprintf(stderr, "A positive number must be supplied for the volume scale.\n");
					return 1;
				}
				fprintf(stderr, "%s", commandError);																		//If it is 0 then the input wasnt a number
				return 1;
			}
			changeVol(left,right,&length,volumeScale);
			fprintf(stderr, "Volume changed by x%.2f\n", volumeScale);
			i++;
		}
		//ECHO
		else if(strcmp(argv[i],"-e") == 0){
			if(i + 1 == argc){																												//Check if last element in the array
				fprintf(stderr, "%s", commandError);
				return 1;
			}
			double delay = 0.0;
			double scale = 0.0;
			i++;
			delay = atof(argv[i]);
			i++;
			scale = atof(argv[i]);
			if((delay <= 0.0) | (scale <= 0.0)){																			//Check if delay and scale are less than or 0
				if((delay < 0.0) | (scale < 0.0)){																			//If its less than zero then its an invalid input
					fprintf(stderr, "Positive numbers must be supplied for the echo delay and scale parameters\n");
					return 1;
				}
				fprintf(stderr, "%s\n", commandError);																	//If it's 0 the input was not a number
				return 1;
			}
			fprintf(stderr, "Echo created on a %.2f delay scaled to %.2f\n", delay, scale);
			echo(&left,&right,delay,scale,&length);
			i++;
		}
		else{
			fprintf(stderr, "%s", commandError);
			return 1;
		}
	}

	head.dataChunk.size = length * 4;																							//resets the size of the audio data
	head.size = head.dataChunk.size + 36;																					//resets the total size of the file in the header

	writeHeader(&head);

	for(i = 0; i < length; i++){
		putchar(left[i] & 0x00FF);																									//puts the second half of the short into the file
		putchar(left[i] >> 8);																											//puts the first half of the short into the file
		putchar(right[i] & 0x00FF);
		putchar(right[i] >> 8);
	}

	free(left);
	free(right);

	return 0;
}

/*readShort
   Description: Reads in two chars and converts to a short
   Parameters:  short* array - The array to to which the short will be added
	 							int index - the index in the array where the short will be stored
   Returns:	    void
*/
void readShort(short* array, int index){
	unsigned char first = getchar();
	unsigned char second = getchar();
	short combined = second << 8;
	combined = combined | first;
	array[index] = combined;
}
/*reverse
   Description: This function will reverse both audio channels
   Parameters:  short* left,right - the arrays to be reversed
	 							int* length - the length of the arrays
   Returns:	    void
*/
void reverse(short* left, short* right, int* length){
	swapValues(left, *length);
	swapValues(right, *length);
}

/*swapValues (Used in Reverse)
   Description: Reverses the arrays, so that it reads backwards
   Parameters:  array* - The array to be reversed
	 							int length - How long said array is
   Returns:	    void
*/
void swapValues(short* array, int length){
	int i = 0;
	short temp;
	for(i = 0; i < length / 2; i++){																							//three line swap to reverse array
		temp = array[i];
		array[i] = array[length - 1 - i];
		array[length - 1 - i] = temp;
	}
}

/*changeSpeed
   Description: This function will change the speed of the file
   Parameters:  short** left, right - the arrays to have their speed changed
	 							double factor - the multiplication factor for changing the speed of the audio files
								int* length - length of the arrays
   Returns:	    void
*/
void changeSpeed(short** left, short** right, double factor, int* length){
	int newLength = *length / factor;
	short* newLeft = (short*)malloc(sizeof(short) * newLength);										//creates new array for updated audio size
	short* newRight = (short*)malloc(sizeof(short) * newLength);									//creates new array for updated audio size
	if((newLeft == NULL) | (newRight == NULL)){
		fprintf(stderr, "Program out of memory\n");
	}

	int i;
	for(i = 0; i < newLength; i++){																								//stores the sped up or slowed down audio info into the new arrays
		newLeft[i] = (*left)[(int)(i * factor)];
		newRight[i] = (*right)[(int)(i * factor)];
	}

	*length = newLength;
	free(*left);
	free(*right);
	*left = newLeft;
	*right = newRight;
}

/*swapValues (Used in Reverse)
   Description: Swaps the right and left channel
   Parameters:  short** left, right - The arrays to be flipped
   Returns:	    void
*/
void flip(short** left, short** right){
	short* temp = *left;
	*left = *right;
	*right = temp;
}

/*fadeOut
   Description: This function fades out the audio over a indicated period of time
   Parameters:  short* left,right - the arrays to be faded out
	 							int* length - the length of the arrays
								double duration - the duration of the fade out in seconds
   Returns:	    void
*/
void fadeOut(short* left, short* right, int* length, double duration){
	int sampleStart = *length - SAMPLERATE * duration;														//calcualtes where in the array to start the fade
	double samples = (duration * SAMPLERATE);
	double fade = 0.0;
	int n = 0;
	int i;

	if(sampleStart < 0){																													//accounts for a fadeTime being longer than the file
		sampleStart = 0;
		n = samples - *length;
	}
	for(i = sampleStart; i < *length && i < samples; i++, n++){										//adds the fade effect to the audio file at given scaling factor
		fade = ((double)(1.0 - (n / samples)) * (double)(1.0 - (n / samples)));			//calculates the fade factor for the audio
		left[i] = (short)(left[i] * fade);
		right[i] = (short)(right[i] * fade);
	}
}

/*fadeIn
   Description: This function fades in the audio over a indicated period of time
   Parameters:  short* left,right - arrays to be faded
	 							int* length - the length of the arrays
								double duration - the amount of time to fade in over.
   Returns:	    void
*/
void fadeIn(short* left, short* right, int* length, double duration){
	double i;
	double samples = (duration * SAMPLERATE);
	double fade = 0.0;

	if(duration < samples){
		samples = *length;
	}
	for(i = 0; i < samples && i < *length; i++){																	//adds the fade effect to the audio file at given scaling factor
		fade = ((i / samples) * (i / samples));																			//calculates the fade factor for the audio
		left[(int)i] = (left[(int)i] * fade);
		right[(int)i] = (right[(int)i] * fade);
	}
}

/*volumeScale
   Description: (used in changeVol) does the actual value changing of an array
   Parameters:  short* array - the array that will have its volume changed
	 							int* length - the length of the array
								double scale - the factor by which the volume is scaled
   Returns:	    void
*/
void volumeScale(short* array, int length, double scale){
	int i = 0;
	for(i = 0; i < length; i ++){
		if(array[i] * scale >= SHRT_MAX)																					//keeps the volume within the max value of a short
			array[i] = SHRT_MAX;
		else if(array[i] * scale <= SHRT_MIN)																		//keeps the volume within the minimum value of a short
			array[i] = SHRT_MIN;
		else
			array[i] = (short)(array[i] * scale);
	}
}

/*changeVol
   Description: Changes the volume of the audio based on the inputted amount
   Parameters:	short* left, right - the arrays to be changed
	 							int* length - the length of the array
								double scale - the amount to change the volume by
   Returns:	    void
*/
void changeVol(short* left, short* right, int* length, double scale){
	volumeScale(left,*length,scale);
	volumeScale(right,*length,scale);
}

/*echo
   Description: This function adds an echo to the audio file
   Parameters:  short** left,right - arrays to have an echo added
	 							double delay - the delay for the echo in seconds
								double scale - the scale of the echo's volume
	 							int* length - the length of the arrays
   Returns:	    void
*/
void echo(short** left, short** right, double delay, double scale, int* length){
	int newLength = *length + (delay * SAMPLERATE);

	short* newRight = (short*)calloc(newLength, sizeof(short));										//creates new array to acount for added echo
	short* newLeft = (short*)calloc(newLength, sizeof(short));

  int i;
	int j;

  for(i = 0; i < *length; i++){																									//copies the old arrays into the new ones
      newLeft[i] = (*left)[i];
      newRight[i] = (*right)[i];
  }
	for(i = delay*SAMPLERATE, j = 0; i < newLength && j < *length; i++, j++){			//adds the echo effect at the specified start time to both arrays
		newLeft[i] = (short)(newLeft[i] + (*left)[j] * scale);
		newRight[i] = (short)(newRight[i] + (*right)[j] * scale);
	}

	*length = newLength;
	free(*left);
	free(*right);
	*left = newLeft;
	*right = newRight;
}