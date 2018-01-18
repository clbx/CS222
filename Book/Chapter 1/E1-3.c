#include <stdio.h>

/* Print F->Table for Fhar = 0, 20, ..., 300*/

main(){
        int fahr, celsius;
        int lower, upper, step;

        lower = 0;
        upper = 300;
        step = 20;

        fahr = lower;
        printf("C\tF\n");
        while(fahr <= upper){
                celsius = 5 * (fahr-32) / 9;
                printf("%d\t%d\n", fahr, celsius); // %d is an integer argument. /t is a tab.
                fahr = fahr+step;
        }
}
