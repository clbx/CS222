/*===================
// CS222: Systems Programming
// Program: Project 1, Something Numbers
// Author: Clay Buxton, Chris Myers
// Date:1/23/17
//===================
*/

#include <stdio.h>                         // Include our Library

//Lazy Caterer's Sequence.
void caterer(){
  printf("Lazy Caterer's Sequence:\n");     //Print Header
  int i, result;                           //Declare loop and result vars
  for(i=0; i < 50; i++){                   //Loop through the 50 requried #'s
    result = ((i*i)+(i+2))/2;              //Run Equation to find max cuts
    printf("%d ", result);                 //Print Result
  }
  printf("\n\n");                            //Put in a new line
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
  while(counter < 50){                     //We want the first 50 primes
    if(isPrime(i)){                        //Check if "i" is prime
      counter++;                           //If it is add one to the counter
      printf("%d ",i);                     //And let the world know
    }
    i++;                                   //Increment 'i'
  }
  printf("\n\n");                            //Put in a new line
}

void fibonacci(){
	long long prev1 = 0, prev2 = 1, currentNumber;
	int i;
	printf("Fibonacci Sequence:");
	printf("\n");
	for(i=0;i<50;i++){
		currentNumber = prev1 + prev2;
		printf("%lld ", currentNumber);
		prev2 = prev1;
		prev1 = currentNumber;
	}
	printf("\n");
	printf("\n");
}

void stoppingtime(){
	int sTimes = 0;
	int i, currentNumber;
	printf("Collatz Stopping Times:");
	printf("\n");
	for(i=1; i<=50; i++){
		currentNumber = i;
		while(currentNumber != 1){
			if((currentNumber%2) != 0)
				currentNumber = (currentNumber*3)+1;
			else
				currentNumber = currentNumber/2;
			sTimes++;
		}
		printf("%d ", sTimes);
		sTimes = 0;
	}
	printf("\n");
	printf("\n");
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
  while(counter < 50){                     //Run until we find 50 happy numbers
    result = i;                            //Make our incremented number the test
    while((result != 4) && (result != 1)){ //As long as the result isnt 4 or 1
      result = getnum(result);             //Run the digit equation
    }
    if(result == 1){                       //1 is happy
      printf("%d ",i);                     //Let the world know
      counter++;                           //More importantly let the counter know
    }
    i++;                                   //increate the tested number
  }
}

int main(){
  caterer();
  primes();
  fibonacci();
  stoppingtime();
  happy();
}
