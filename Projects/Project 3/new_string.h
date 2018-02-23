#include <stddef.h>


char* new_strcopy(char* destination, const char* source){//Conor
}

char* new_strncpy(char* destination, const char* source, size_t n){//Conor

}

int new_strcmp(const char* string1, const char* string2){//Conor

}

int new_strncmp(const char* string1, const char* string2, size_t n){//Conor

}

char* new_strcat(char* destination, const char* source){//Clay
  //First get the lengths of the two Stings
  int i = 0, desLen = 0, sourceLen = 0;
  for(i = 0; destination[i] != '\0'; i++){
    desLen++;
  }
  for(i = 0; source[i] != '\0'; i++){
    sourceLen++;
  }
  //Now we have the legnths of the two strings.
  int catLen = sourceLen + desLen;
  char catString[catLen];
  for(i = 0; i < sourceLen-2; i++){
    catString[i] = destination[i];
  }
  for(i = sourceLen-1; i < desLen -1; i ++){
    catString[i] = source[i];
  }
  return catString;
}

char* new_strncat(char* desintation, const char* source, size_t n){//Clay

}

size_t new_strnlen(const char* string){//Clay

}

char* new_strnchr(const char* string, int character){//Clay

}

char* new_strstr(const char* haystack, const char* needle){//Clay

}
