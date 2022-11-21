#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "exchange.h"

// Define upper limit for random number range
#define UPPER_RANDOM 10

// Declare functions
void printMatrix(float** matrix, int n);

// Main Function
int main(int argc, char** argv)
{
    // Declare matrix dimension value
    int n;
    
    // Input dimension of square matrix
    printf("Enter dimension of square matrix:");
    scanf("%d", &n);

    // Initialize random seed
    srand((unsigned int)time(NULL));

    // Declare n x n matrix
    float** matrix;

    // Declare indexes
    int i, j;

    /* Allocate memory for matrix rows */
    matrix = (float**)malloc(sizeof(float*) * 2);

    for(i=0; i<n; i++)
    {
        /* Allocating memory for the column elements of each row*/
        matrix[i] = (float*)malloc(sizeof(float) * 5);
        for(j=0; j<n; j++)
        {
            matrix[i][j] = ((float)rand()/RAND_MAX)*(float)(UPPER_RANDOM);            
        }
    } 

    // Print Matrix to verify correct construction
    printMatrix(matrix, n);

    // Transpose the matrix
    for(i=0; i<n; i++)
    {        
        for(j=i+1; j<n; j++)
        {            
            exchange(&matrix[i][j], &matrix[j][i]);        
        }
    }

    // Print Matrix to verify correct swap
    printMatrix(matrix, n);

    /* Free matrix memory at last */
    for(int i=0; i<2; i++) /*Releasing memory */
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}

/* This functions receives a 2-D matrix and prints it in console*/
void printMatrix(float** matrix, int n)
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            // Print each element of the matrix
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
} // End of Function printMatrix