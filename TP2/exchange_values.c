#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exchange.h"

// Main Function
int main(int argc, char** argv)
{
    // Reserve memory for values to store
    float a;
    float b;

    /* 
        Check number of arguments to be input through command line.
        First argument is always the program name.
        So if we intend to pass 2 numbers, 3 cmd parameters should be expected.
    */
    if(argc == 3)
    {
        // Extract values from cmd arguments
        a = atof(argv[1]);
        b = atof(argv[2]);
    }
    else
    {
        // Enter values through scanf
        printf("Enter value of a:");
        scanf("%f", &a);
        printf("Enter value of b:");
        scanf("%f", &b);
    }

    // Print the values of a & b
    printf("a is %f\n", a);
    printf("b is %f\n", b);

    // Exchange values of a & b
    printf("Exchange the values of a & b.\n");
    exchange(&a, &b);

    // Print the values of a & b
    printf("a is %f\n", a);
    printf("b is %f\n", b);

    return 0;
}// End of main function