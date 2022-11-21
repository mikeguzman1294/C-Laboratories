#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Declare function to generate a uniform sample
float generate_uniform_sample(float x, float u, float o);

// Main Function
int main(int argc, char** argv)
{    
    // Extract values from cmd arguments
    float mean = atof(argv[1]);
    float std_dev = atof(argv[2]);
    float samples = atof(argv[3]);    
    
    //printf("Mean: %f\n", mean);
    //printf("Standard Deviation: %f\n", std_dev);
    //printf("Number of Samples: %f\n", samples);
    
    // Declare a variable to save the current sample
    float sample;
    // Define the step size as 6*omega / number of samples
    float step_size = ( 6 * std_dev ) / samples;
    // Initialize the first step to be -3*omega
    float step = mean - (3 * std_dev);
    
    // Create a file to save the samples to be consumed by gnuplot
    FILE *tfile;
    tfile = fopen("gaussian_samples", "w");
    
    if(tfile != NULL)
    {
        for (int i = 0; i < samples; i++)
        {
            // Generate a sample for the current step
            sample = generate_uniform_sample(step, mean, std_dev);
            // Save the step and its corresponding uniform distribution sample
            fprintf(tfile, "%f %f\n", step, sample);
            step = step + step_size;
        }      
    }        
    fclose(tfile);

    // Call gnuplot from system command line
    system("gnuplot -persist -e \"plot 'gaussian_samples'\"");    

    return 0;
}// End of main function


// Definition of the function to generate a uniform sample
float generate_uniform_sample(float x, float u, float o)
{
    float sample;

    sample = ( 1 / sqrt( 2 * M_PI * pow(o, 2) ) ) * exp( -( pow(x-u, 2) /  (2 * pow(o,2)) ) );

    return sample;
} // End of function generate_uniform_sample