#include <stdio.h>
#include "convert.h"

//I'm not sure if \r is used in any other use case, but this makes sure that
//It's only taken out in the senario of a \r\n.

int main(){
  int c, flag=0;        //Declaring the char value & flag for checking next val
  c = getchar();        //Get the first char
  while(c != EOF){      //Until its the end of the file
    if(flag){           //If the last charactar was \r
      if(c == NL){      //If this is \n
        flag = 0;       //Reset the flag
      }
      else{
        putchar(LF);    //If not put everything back
        putchar(c);     //And the next one
        flag = 0;       //Reset the flag
      }
    }
    else{               //If the flag has not been triggered
      if(c == LF){      //Check to see if the char is \r
        flag = 1;       //If it is, set flag to 1
      }
      else{             //If it's not, just put the char into the output
        putchar(c);
      }
      c = getchar();    //Get the next char
    }
  }
  if(flag){             //Putting the final newline at the end of the file.
    putchar(LF); 
  }
}
