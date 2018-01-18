#include <stdio.h>

/* Print F->Table for Fhar = 0, 20, ..., 300*/

main(){
        int fahr, celsius;
        int lower, upper, step;

        lower = 0;
        upper = 300;
        step = 20;

        celsius = lower;
        printf("C\tF\n");
        while(celsius <= upper){
                fahr = (celsius + 32) * 9 / 5;
                printf("%d\t%d\n", fahr, celsius); // %d is an integer argument. /t is a tab.
                celsius = celsius+step;
        }
}

