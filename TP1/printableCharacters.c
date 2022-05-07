#include <ctype.h>
#include <stdio.h>

// Define looping parameters to avoid magic numbers
#define ZERO 0
#define MAX_ASCII_DECIMAL 127

// Main Function
int main()
{
    // Initialize counter to count number of printable characters within loop range
    int counter = 0;
    
    // Loop through all existing ASCII values
    for(int c = ZERO; c <= MAX_ASCII_DECIMAL; c++)
    {
        // Print the character along its index if it is printable
        if (isprint(c)!= 0)
        {
            //printf("ASCII decimal number: %d - ASCII character: %c\n", c, c);
            printf("\nASCII decimal number: %d - ASCII character: ", c);
            putchar(c);
            counter++;
        }
    } // end of for loop

    // Print total number of printable characters found within set range
    printf("\n\nThere are %d printable characters from decimal number %d to %d.", counter, ZERO, MAX_ASCII_DECIMAL);

    return 0;
}// End of main function