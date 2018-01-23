#include <stdio.h>


//Lazy Caterer's Sequence.
void caterer(){
  printf("Lazy Caterer's Sequence\n");     //Print Header
  int i, result;                           //Declare loop and result vars
  for(i=0; i < 50; i++){                   //Loop through the 50 requried #'s
    result = ((i*i)+(i+2))/2;              //Run Equation to find max cuts
    printf("%d ", result);                 //Print Result
  }
  printf("\n");                            //Put in a new line
}

//Prime Numbers
int isPrime(int in){                       //Indivudal Number Checker
  int i;                                   //Loop Variable
  for(i=2; i <= in/2; i++){                //Slightly more effcient prime check
    if(in % i == 0){                       //Checking if it divides evenly
        return 0;                          //Returns false if it does
    }
  }
  return 1;                                //Otherwise it returns true
}

void primes(){                             //A Main Prime Checker
  printf("Prime Numbers:\n");              //Header
  int counter=0,i=1;                       //Declaring loop var & prime counter
  while(counter <= 50){                    //We want the first 50 primes
    if(isPrime(i)){                        //Check if "i" is prime
      counter++;                           //If it is add one to the counter
      printf("%d ",i);                     //And let the world know
    }
    i++;                                   //Increment 'i'
  }
  printf("\n");                            //Put in a new line
}

//Fibonacci
//Collatz Stopping Time
//Happy Numbers
int runequation(int in){
  int total=0;
  while(1){
    while(in > 0){
      total+=((in%10)+(in%10));
      in = in/10;
    }
    if(total==1){
      return 1;
      break;
    }
    else if(total == 4){
      return 0;
      break;
    }
  }
}


int main(){
  //caterer();
  //primes();
  //Fibonacci
  //Collatz Stopping Times
  //Happy Numbers.

  int happy = runequation(7);
  printf("%d", happy);


}
