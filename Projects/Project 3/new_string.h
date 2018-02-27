#include <stddef.h>
/*******************************
*
*  Project Name: Project 3: "String 'Em Up"
*  Description: Re-creating the string library, for some cool string tools
*  File names: new_string.h
*  Date: Friday, March 2, 2018
*  Authors: Clay Buxton (buxtonc@etown.edu) Conor Csongradi (csongradic@etown.edu)
*
*******************************/



size_t new_strnlen(const char* string);







char* new_strcpy(char* destination, const char* source)
{

	int size = 0;
	while(source[size]!='\0')
		size++;

	int i = 0;
	for(i=0; i<=size; i++)
		destination[i] = source[i];

	return destination;

}

char* new_strncpy(char* destination, const char* source, size_t n)
{
	int i = 0;

	for(i=0; i < n; i++)
		destination[i] = source[i];
	destination[i+1] = '\0';

	return destination;
}

int new_strcmp(const char* string1, const char* string2)
{
	int i = 0;
	int size1 = 0;
	int size2 = 0;

	while(string1[size1]!='\0')
		size1++;
	while(string2[size2]!='\0')
		size2++;

	for(i=0; i<size1 && i<size2; i++)
	{
		if(string1[i]<string2[i])
			return -1;
		if(string1[i]>string2[i])
			return 1;
	}

	if(i<size1)
		return 1;
	if(i<size2)
		return -1;

	return 0;

}

int new_strncmp(const char* string1, const char* string2, size_t n)
{
	int i = 0;
	int size1 = 0;
	int size2 = 0;

	while(string1[size1]!='\0')
		size1++;
	while(string2[size2]!='\0')
		size2++;

	if(n<size1 && n<size2)
	{
		for(i=0; i<n; i++)
		{
			if(string1[i]<string2[i])
				return -1;
			if(string1[i]>string2[i])
				return 1;
		}

		return 0;
	}
	else
	{
		for(i=0; i<size1 && i<size2; i++)
		{
			if(string1[i]<string2[i])
				return -1;
			if(string1[i]>string2[i])
				return 1;
		}

		if(i<size1)
			return 1;
		if(i<size2)
			return -1;

		return 0;
	}

}


char* new_strcat(char* destination, const char* source){//Clay DONE
  size_t desLen = new_strnlen(destination);
  size_t sourceLen = new_strnlen((char*)source);
  size_t i = 0;
  for(i = 0; i < sourceLen; i++)
    destination[desLen+i] = source[i];
  destination[desLen+sourceLen] = '\0';
  return destination;
}

char* new_strncat(char* destination, const char* source, size_t n){//Clay DONE
  size_t desLen = new_strnlen(destination);
  size_t i = 0;
  for(i = 0; i <= n; i++)
    destination[desLen+i] = source[i];
  destination[desLen+n] = '\0';
  return destination;
}

size_t new_strnlen(const char* string){//Clay DONE
  size_t i = 0;
  for(i = 0; string[i] != '\0'; i++);
  return i;
}

char* new_strnchr(const char* string, int character){//Clay
  int i = 0;
  char* foundchar;
  for(i = 0;string[i] != '\0'; i++){
    if(string[i] == character){
      foundchar = (char*)&string[i];
      return foundchar;
    }
  }
  return NULL;
}

char* new_strstr(const char* haystack, const char* needle){//Clay
}
