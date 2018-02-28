#include <stddef.h>
#include "new_string.h"
/*******************************
*
*  Project Name: Project 3: "String 'Em Up"
*  Description: Re-creating the string library, for some cool string tools
*  File names: new_string.h
*  Date: Friday, March 2, 2018
*  Authors: Clay Buxton (buxtonc@etown.edu) Conor Csongradi (csongradic@etown.edu)
*
*******************************/



/* STRING COPY
   Description: Copies the characters from source into destination.
   Parameters: char* destination: where the the source string is going to. char*
	 						 source: where the string is coming from.
   Returns: char*, a copied string
*/
char* new_strcpy(char* destination, const char* source){
	size_t size = new_strlen(source);
	size_t i = 0;
	for(i=0; i<=size; i++)
		destination[i] = source[i];
	return destination;
}

/* STRING N COPY
   Description: Copies the first n characters from source into destination. If
	 the function hits a null character in source before it has copied n
	 characters, the remaining characters are filled with null characters.
   Parameters: char* destination: where the characters are going to, char*
	 source: where the characters are coming from, size_t n: How many characters
	 to copy
   Returns: char *, a copied string
*/
char* new_strncpy(char* destination, const char* source, size_t n)
{
	int i = 0;

	for(i=0; i < n; i++)
		destination[i] = source[i];
	destination[i+1] = '\0';

	return destination;
}

/* STRING COMPARE
   Description: Compares two strings. The return value is positive if string1
	 comes after string2 alphabetically, negative if string1 comes before string2
	 alphabetically, and 0 if the two strings are equal.
   Parameters: char* string1: the 1st string to be compared, char* string2 the
	 2nd string to be compared
   Returns: -1 if string1 is "less than" string2, 1 if string1 is "greater than"
	 string2 and 0 if they're the same.
*/
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

/*STRING N COMPARE
   Description:  Compares two strings exactly like new_strcmp(), except
	 comparing at most the first n characters.
   Parameters: char* string1: the 1st string to be compared, char* string2: the
	 2nd string to be compared, size_t n: how many characters to compare
   Returns: -1 if string1 is "less than" string2, 1 if string1 is "greater than"
	 string2 and 0 if they're the same.
*/
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

/*STRING CONCATNATE
   Description: Adds the string contained in source to the end of the string
	 contained in destination. The values in destination are modified, but a
	 pointer to destination is also returned.
   Parameters:
   Returns:
*/
char* new_strcat(char* destination, const char* source){//Clay DONE
  size_t desLen = new_strlen(destination);
  size_t sourceLen = new_strlen((char*)source);
  size_t i = 0;
  for(i = 0; i < sourceLen; i++)
    destination[desLen+i] = source[i];
  destination[desLen+sourceLen] = '\0';
  return destination;
}
/*
   Description:
   Parameters:
   Returns:
*/
char* new_strncat(char* destination, const char* source, size_t n){//Clay DONE
  size_t desLen = new_strlen(destination);
  size_t i = 0;
  for(i = 0; i <= n; i++)
    destination[desLen+i] = source[i];
  destination[desLen+n] = '\0';
  return destination;
}
/*
   Description:
   Parameters:
   Returns:
*/
size_t new_strlen(const char* string){//Clay DONE
  size_t i = 0;
  for(i = 0; string[i] != '\0'; i++);
  return i;
}
/*
   Description:
   Parameters:
   Returns:
*/
char* new_strchr(const char* string, int character){//Clay DONE
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
/*
   Description:
   Parameters:
   Returns:
*/
char* new_strstr(const char* haystack, const char* needle){//Clay


}
