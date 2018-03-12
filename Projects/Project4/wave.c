#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int readHeader( WaveHeader* header )
{	
	if( fread( header, sizeof( WaveHeader ), 1, stdin) != 1 )
		return 0;	
		
	return 1;	
}

int writeHeader( const WaveHeader* header )
{	
	if( fwrite( header, sizeof( WaveHeader ), 1, stdout) != 1 )			
		return 0;	
		
	return 1;	
}