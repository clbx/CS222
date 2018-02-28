#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int main(){
  char** board = (char**)malloc(sizeof(char*)*8);
  int i;
  for(i = 0; i < 8; ++i){
    board[i] = (char*)malloc(sizeof(char)*8);
  }

  srand(time(NULL));
  int j;
  for(i = 0; i < 8; i++){
    for(j = 0; j < 8; j++){
      int value = rand() % 8;
      if(value == 0)
        board[i][j] = 'Q';
      else
        board[i][j] = ' ';
    }
  }
}
