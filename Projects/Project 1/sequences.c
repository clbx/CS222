/*===================
// CS222: Systems Programming
// Program: Project 1, Something Numbers
// Author: Clay Buxton, Chris Myers
// Date:1/23/17
//===================
*/

#include <stdio.h>                         // Include our Library
#define MAX_COUNT 50


//Lazy Caterer's Sequence.
void caterer(){
  printf("Lazy Caterer's Sequence:\n");    //Print Header
  int i, result;                           //Declare loop and result vars
  for(i=0; i < MAX_COUNT; i++){            //Loop through the 50 requried #'s
    result = ((i*i)+(i+2))/2;              //Run Equation to find max cuts
    printf("%d ", result);                 //Print Result
  }
  printf("\n\n");                          //Put in a new line
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
  int counter=0,i=2;                       //Declaring loop var & prime counter
  while(counter < MAX_COUNT){              //We want the first 50 primes
    if(isPrime(i)){                        //Check if "i" is prime
      counter++;                           //If it is add one to the counter
      printf("%d ",i);                     //And let the world know
    }
    i++;                                   //Increment 'i'
  }
  printf("\n\n");                          //Put in a new line
}

void fibonacci(){                          //The Fibonacci Sequence
	long long prev1=0,prev2=1,currentNumber; //Declare vars. 2 previous & current
	int i;                                   //loop int
	printf("Fibonacci Sequence:\n");         //Header sequence
	for(i=0;i < MAX_COUNT ;i++){             //We want the first 50 numbers
		currentNumber = prev1 + prev2;         //Fibonaccis sequence
		printf("%lld ", currentNumber);        //printing current number
		prev2 = prev1;                         //Resetting our previous numbers
		prev1 = currentNumber;
	}
	printf("\n\n");                          //Put in a new line
}

void stoppingtime(){                       //Collatz Stopping Time
	int i, sTimes = 0, currNum;              //Declaring our varibles
	printf("Collatz Stopping Times:\n");     //Print Header
	for(i=1; i <= MAX_COUNT; i++){           //Loop until we get 50 numbers
    currNum = i;
		while(currNum != 1){                   //As long as our number isnt I
			if((currNum%2) != 0)                 //Run the equation pt.1
				currNum = (currNum*3)+1;           //Run the equation pt.2
			else
				currNum = currNum/2;               //Run the equation pt.3
			sTimes++;                            //Increment the sTimes
		}
		printf("%d ", sTimes);                 //Let the world know
		sTimes = 0;                            //Reset
	}
	printf("\n\n");                          //Put in our spacers
}

//Happy Numbers
int getnum(int in){                        //Gets number by squaring digits
  int total=0, digit;                      //Declaring our vars
  while(in > 0){                           //Until the number no longer is there
    //printf("%d\n", total);               //Debugging printout
    digit = in%10;                         //Get the least signifigant digit
    //printf("Digit: %d \n", digit)        //Debugging printout
    total+=digit*digit;                    //Add it to our running total
    in = in/10;                            //Then divide by 10 to remove it.
  }
  return total;                            //Return the finished number
}

void happy(){                              //Finding happy numbers
  printf("Happy Numbers:\n");              //Header
  int counter = 0,i=1,result=0;            //Declaring Vars
  while(counter < MAX_COUNT){              //Run until we find 50 happy numbers
    result = i;                            //Make incremented number the test
    while((result != 4) && (result != 1)){ //As long as the result isnt 4 or 1
      result = getnum(result);             //Run the digit equation
    }
    if(result == 1){                       //1 is happy
      printf("%d ",i);                     //Let the world know
      counter++;                           //Let the counter know
    }
    i++;                                   //increate the tested number
  }
  printf("\n");                            //Add Newline
}

int main(){                                //Run everything
  caterer();                               //Run Caterer
  primes();                                //Run Primes
  fibonacci();                             //Run Fibonacci
  stoppingtime();                          //Run Stopping Time
  happy();                                 //Run Happy Numbers
}
