#ifndef WAVE_H
#define WAVE_H

typedef struct _FormatChunk
{
	unsigned char	ID[4];
	unsigned int	size;
	unsigned short	compression;
	unsigned short	channels;
	unsigned int	sampleRate;
	unsigned int	byteRate;
	unsigned short	blockAlign;
	unsigned short	bitsPerSample;
} FormatChunk;

typedef struct _DataChunk
{
	unsigned char	ID[4];
	unsigned int	size;
} DataChunk;

typedef struct _WaveHeader
{
	unsigned char	ID[4];
	unsigned int	size;
	unsigned char	format[4];
	FormatChunk		formatChunk;
	DataChunk		dataChunk;
} WaveHeader;



int readHeader( WaveHeader* header );
int writeHeader( const WaveHeader* header );

#endif
