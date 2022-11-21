#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functions.h"

// Declare function to generate a uniform sample
//float generate_uniform_sample(float x, float u, float o);

// Main Function
int main(int argc, char** argv)
{    
    // Call wget from system command line to import given website html information into a text file in local drive
    system("wget --quiet --output-document=usinenouvelle.txt https://www.usinenouvelle.com/comparatif-des-ecoles-d-ingenieurs-2022");

    



    return 0;
}// End of main function


/*// Definition of the function to generate a uniform sample
float generate_uniform_sample(float x, float u, float o)
{
    float sample;

    sample = ( 1 / sqrt( 2 * M_PI * pow(o, 2) ) ) * exp( -( pow(x-u, 2) /  (2 * pow(o,2)) ) );

    return sample;
} // End of function generate_uniform_sample*/