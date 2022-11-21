#include <stdio.h>
#include <stdlib.h>

// Main Function
int main()
{
    // Declare main function variables
	float *buffer;
	int input_size;
	
	// Open the binary file
   	FILE *input_file;
   	input_file = fopen("function_data_bin", "rb");

	// Create a file to save the samples to be consumed by gnuplot
   	FILE *output_file;
   	output_file  = fopen("function_data_text.txt", "w");

   	if(input_file != NULL)
	{
   		// Get the size of the binary file
   		fseek(input_file, 0, SEEK_END);
   		input_size= ftell(input_file);   		
    		
   		// Memory allocation for the buffer
   		fseek(input_file, 0, SEEK_SET);
   		buffer= (float *)malloc(sizeof(float)*input_size);
		
		// Read input binary file into the buffer
       	fread(buffer, sizeof(float), input_size, input_file);

		// Close the input file
    	fclose(input_file);
        	
      	// Bytes are divided by pairs of 4 bytes each, 8 bits in total 
		int i=0;
		while( i < input_size / 8)
		{
			fprintf(output_file, "%f %f\n", buffer[i], buffer[i+200]);
			i++;
		}
		
		// Close the output file
    	fclose(output_file);					
    }

	// Free the allocated memory for the buffer
    free(buffer);	

	// Call gnuplot from system command line
   	system("gnuplot -p -e \"plot 'function_data_text.txt'\"");

	return 0;
} // End of main function