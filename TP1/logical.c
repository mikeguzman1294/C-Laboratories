#include<stdio.h>

// logical_operator_use Function Definition
void logical_operator_use(char x)
{
    // Declare local variables to test logical operators
    int a, b;

    // Use switch case for readability
    switch (x)
    {
    case 'A':
        printf("\nAND OPERATOR TRUTH TABLE\nA\tB\tAND\n");
        a = 0, b = 0;
        printf("%d\t%d\t%d\n", a, b, a&&b);
        a = 0, b = 1;
        printf("%d\t%d\t%d\n", a, b, a&&b);
        a = 1, b = 0;
        printf("%d\t%d\t%d\n", a, b, a&&b);
        a = 1, b = 1;
        printf("%d\t%d\t%d\n", a, b, a&&b);
        break;
    case 'O':
        printf("\nOR OPERATOR TRUTH TABLE\nA\tB\tOR\n");
        a = 0, b = 0;
        printf("%d\t%d\t%d\n", a, b, a||b);
        a = 0, b = 1;
        printf("%d\t%d\t%d\n", a, b, a||b);
        a = 1, b = 0;
        printf("%d\t%d\t%d\n", a, b, a||b);
        a = 1, b = 1;
        printf("%d\t%d\t%d\n", a, b, a||b);
        break;
    case 'X':
        printf("\nXOR OPERATOR TRUTH TABLE\nA\tB\tXOR\n");
        a = 0, b = 0;
        printf("%d\t%d\t%d\n", a, b, a^b);
        a = 0, b = 1;
        printf("%d\t%d\t%d\n", a, b, a^b);
        a = 1, b = 0;
        printf("%d\t%d\t%d\n", a, b, a^b);
        a = 1, b = 1;
        printf("%d\t%d\t%d\n", a, b, a^b);
        break;
    default:
        printf("Entered unvalid character.");
        break;
    }// End of switch case
}// End of logical_operator_use function