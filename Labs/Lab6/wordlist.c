#include <stdio.h>
#include <string.h>

void reverse(char** argv, int argc);
void printstr(char** argv, int argc);
void backwards(char** argv, int argc);
void sort(char** argv, int argc);

int main(int argc, char** argv){
  /*
  Would have put in to check for each case then run the appropriate function(s)
  */
  if(argc < 2){
    printf("Enter a modifier and an input.\n");
  }
  //get the total amount of commands
  int k = 0, commandlen = 0;
  for(k = 0; argv[1][k] != '\0'; k++){
    commandlen++;
  }
  //Now execute the commands
  int i = 0;
  for(i = 1; i < commandlen; i++){
    //printf("%c\n", argv[1][i]);
    if(argv[1][i] == 'b'){
      //printf("Backwards \n");
      backwards(argv, argc);
    }
    else if(argv[1][i] == 'r'){
      //printf("Reversing \n");
      reverse(argv, argc);
    }
    else if(argv[1][i] == 's'){
      //printf("Sorting \n");
      sort(argv,argc);
    }
  }
  printstr(argv, argc);
}

//Backwards and Reverse work
void backwards(char** argv, int argc){
  //Acutal words starts at 2
  int i = 0, k = 0, wordlen = 0, start = 0, end = 0, temp = 0;
  for(i = 2; i < argc; i++){
    //Get length of that word
    for(k = 0; argv[i][k] != '\0'; k++){
      wordlen++;
    }
    start = 0;
    end = wordlen-1;
    while(start < end){
      temp = argv[i][start];
      argv[i][start] = argv[i][end];
      argv[i][end] = temp;
      start++;
      end--;
    }
    wordlen = 0;
  }
}

void reverse(char** argv, int argc){
  int start = 2;
  int end = argc -1;
  char* temp = argv[2];
  while(start < end){
    temp = argv[start];
    argv[start] = argv[end];
    argv[end] = temp;
    start++;
    end--;

  }
}

void printstr(char** argv, int argc){
  int i = 0;
  for(i = 2;i < argc;i++){
    printf("%s ", argv[i]);
  }
}

void sort(char** argv, int argc){
  int i = 0, flag = 1;
  char* temp = argv[2];
  while(flag){
    flag = 0;
    for(i = 2; i < argc-1; i++){
      if(strcmp(argv[i], argv[i+1]) > 0){
        //printf("Not in order yet!\n");
        flag = 1;
        temp = argv[i];
        argv[i] = argv[i+1];
        argv[i+1] = temp;
      }
    }
  }
}
