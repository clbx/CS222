#include "new_string.h"
#include <string.h>
#include <stddef.h>
#include <stdio.h>


int main(){


  char string[256];
  const char string2[] = "Hello my name is Clay";
  scanf("%s", string);

  printf("%p", new_strnchr(string2,'n'));
  return 1;
}
