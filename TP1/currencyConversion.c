#include <stdio.h>

// Define conversion constants
#define EURO_TO_US 1.05
#define US_TO_EURO 0.95
#define US_TO_POUND 0.81
#define POUND_TO_US 1.23
#define EURO_TO_POUND 0.85
#define POUND_TO_EURO 1.17

// Main Function
int main()
{
    // Main function variables
    int choice;
    float amount;
    int conversion;
    
    // Prompt user to choose currency to convert
    printf("Choose the currency to convert.\n");
    printf("For EUROS, enter '1'.\n");
    printf("For US DOLLARS, enter '2'.\n");
    printf("For POUNDS, enter '3'.\n");
    printf("Enter your choice:\n");
    scanf("%d", &choice);

    // Prompt user to define the amount of the currency to convert
    printf("Enter the amount to convert\n");
    scanf("%f", &amount);

    switch (choice)
    {
    case 1:
        printf("\nChoose to what currency to convert.\n");
        printf("For US DOLLARS, enter '1'.\nConversion rate: %.2f\n", EURO_TO_US);
        printf("For POUNDS, enter '2'.\nConversion rate: %.2f\n", EURO_TO_POUND);
        printf("Enter your choice:\n");
        scanf("%d", &conversion);

        switch (conversion)
        {
        case 1:
            printf("%.2f EUROS = %.2f US DOLLARS\n", amount, amount * EURO_TO_US);
            break;
        case 2:
            printf("%.2f EUROS = %.2f POUNDS\n", amount, amount * EURO_TO_POUND);
            break;        
        default:
            printf("No valid value was entered.\n");
            break;
        }
        break;
    
    case 2:
        printf("\nChoose to what currency to convert.\n");
        printf("For EUROS, enter '1'.\nConversion rate: %.2f\n", US_TO_EURO);
        printf("For POUNDS, enter '2'.\nConversion rate: %.2f\n", US_TO_POUND);
        printf("Enter your choice:\n");
        scanf("%d", &conversion);

        switch (conversion)
        {
        case 1:
            printf("%.2f US DOLLARS = %.2f EUROS\n", amount, amount * US_TO_EURO);
            break;
        case 2:
            printf("%.2f US DOLLARS = %.2f POUNDS\n", amount, amount * US_TO_POUND);
            break;        
        default:
            printf("No valid value was entered.\n");
            break;
        }
        break;

    case 3:
        printf("\nChoose to what currency to convert.\n");
        printf("For EUROS, enter '1'.\nConversion rate: %.2f\n", POUND_TO_EURO);
        printf("For US DOLLARS, enter '2'.\nConversion rate: %.2f\n", POUND_TO_US);
        printf("Enter your choice:\n");
        scanf("%d", &conversion);

        switch (conversion)
        {
        case 1:
            printf("%.2f POUNDS = %.2f EUROS\n", amount, amount * POUND_TO_EURO);
            break;
        case 2:
            printf("%.2f POUNDS = %.2f US DOLLARS\n", amount, amount * POUND_TO_US);
            break;        
        default:
            printf("No valid value was entered. Exiting program . . .\n");
            break;
        }
        break;

    default:
        printf("No valid currency was entered. Exiting program . . .\n");
        break;
    }

    return 0;
}// End of main function