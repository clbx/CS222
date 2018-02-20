#include <stdio.h>
#include <string.h>

int main(int argc, char** argv){
  if(argc != 2){
    printf("Enter a modifier dumbass.\n");
  }
  else{
    if(strcmp(argv[1], "-y") == 0)
      printf("ISSA YAK BITCH\n");
    if(strcmp(argv[1], "-t") == 0)
      printf("BRUH ITS A DEVIL\n");
    if(strcmp(argv[1], "-c") == 0)
      printf("I DONT EVEN KNOW TF THAT IS\n");
  }

}
